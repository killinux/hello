#include <ngx_config.h> 
#include <ngx_core.h> 
#include <ngx_http.h> 
#include <ngx_buf.h> 
static  char *ngx_http_hello_world(ngx_conf_t *cf ,ngx_command_t *cmd,void *conf); 
//*cf ָ��ngx_conf_t �ṹ��ָ�룬��ָ����洫�����Ĳ��� 
//*cmd ָ��ǰ�ṹ��ngx_command_t ��ָ��(����ָ) 
//*confָ���Զ���ģ�����ýṹ���ָ�� 
//cf: �ò������汣�����ȡ����������Ϣ��ԭʼ�ַ����Լ���ص�һЩ��Ϣ���ر�ע��������������args�ֶ���һ��ngx_str_t���͵����飬ÿ������Ԫ�ء���������׸�Ԫ�����������ָ�����ַ������ڶ���Ԫ�����׸�������������Ԫ���ǵڶ����������������ơ�
//cmd: �������ָ���Ӧ��ngx_command_t�ṹ��
//conf: ���Ƕ���Ĵ洢�������ֵ�Ľṹ�壬����������չʾ���Ǹ�ngx_http_hello_loc_conf_t�����������hello_string������ʱ�򣬴����conf��ָ��һ��ngx_http_hello_loc_conf_t���͵ı������û��ڴ����ʱ�����ʹ������ת����ת�����Լ�֪�������ͣ��ٽ����ֶεĸ�ֵ��
static ngx_command_t ngx_http_hello_world_commands[]={ 
        { 
                ngx_string("hello_world"),//ָ�����ƣ�nginx.conf��ʹ�� 
                NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,  //ע��1 
                ngx_http_hello_world,//�ص����� �����涨��Ĵ��������� 
                0,//���ֵ�ֵ�ŵ�λ�ã�ȫ�֣�server��location 
                0,//ָ���ֵ�����λ�� 
                NULL //һ�㶼ΪNULL 
        }, 
        ngx_null_command  //����ngx_null_command ָ���ֹͣ 
}; 
static u_char ngx_hello_world[]="hello world"; 
//ngx_http_<module name>_module_ctx���ڴ����ͺϲ��������� 
//�ο�http/ngx_http_config.h 
static ngx_http_module_t ngx_http_hello_world_module_ctx={ 
        NULL,//preconfiguration 
        NULL,//postconfiguration 
        NULL,//create main configuration 
        NULL,//init main configuration 
        NULL,//create server configuration 
        NULL,//merge server configuration 
        NULL,//create location configuration 
        NULL //merge localtion configuration 
}; 
//nginx���̣��߳���أ�ngx_http_<module name>_module 
//���ģ��Ķ����ǰ����ݴ���������ض�ģ��Ĺؼ� 
ngx_module_t ngx_http_hello_world_module={ 
        NGX_MODULE_V1, 
        &ngx_http_hello_world_module_ctx,//module context 
        ngx_http_hello_world_commands,  //module directives 
        NGX_HTTP_MODULE,	        //module type 
        NULL,	 //init master 
        NULL,	 //init module 
        NULL,	 //init process 
        NULL,	 //init thread 
        NULL,	 //exit thread 
        NULL,	 //exit process 
        NULL,	 //exit master 
        NGX_MODULE_V1_PADDING 
}; 
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r) 
{ 
        ngx_buf_t *b; 
        ngx_chain_t out; 

        r->headers_out.content_type.len =sizeof("text/plain")-1; 
        r->headers_out.content_type.data=(u_char *) "text/plain"; 

        b=ngx_pcalloc(r->pool,sizeof(ngx_buf_t)); 

        out.buf=b; 
        out.next=NULL; 

        b->pos=ngx_hello_world; 
        b->last=ngx_hello_world+sizeof(ngx_hello_world); 
        b->memory=1; 
        b->last_buf=1; 

        r->headers_out.status=NGX_HTTP_OK; 
        r->headers_out.content_length_n=sizeof(ngx_hello_world); 
        ngx_http_send_header(r); 

        return ngx_http_output_filter(r,&out); 
} 
//�ص�������1���location�еġ����ġ��ṹ�壬2Ϊ������������� 
static char *ngx_http_hello_world(ngx_conf_t *cf,ngx_command_t *cmd,void *conf) 
{ 
        ngx_http_core_loc_conf_t *clcf; 

        clcf=ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module); 
        clcf->handler=ngx_http_hello_world_handler; 
        return NGX_CONF_OK; 
} 
