set nocompatible
source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin

set diffexpr=MyDiff()
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let eq = ''
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      let cmd = '""' . $VIMRUNTIME . '\diff"'
      let eq = '"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3 . eq
endfunction

" ############### Gui��NoGui��ͳһ���� ��ʼ ##################
"����˵����루����gvim��������ģʽ�£�
set nocompatible
set backspace=2

source $VIMRUNTIME/vimrc_example.vim
if has('win32')
    source $VIMRUNTIME/mswin.vim
    behave mswin
endif

" �ļ�������ļ����ַ���
let &termencoding=&encoding
set fileformat=unix
set fileformats=unix
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set fileencoding=utf-8 " �½��ļ�ʹ�õı���
set langmenu=zh_CN
let $LANG = 'zh_CN.UTF-8'
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim

"�ļ����ͼ��, �������ſ��������ܲ�ȫ
filetype on
filetype plugin on
filetype indent on

"��ʾ�к�
set nu!
"set ruler

"Vim ��ʵ�������������Լ�<>���Զ���ȫ"
inoremap [ []<ESC>i
inoremap { {}<ESC>i
inoremap < <><ESC>i
inoremap " ""<ESC>i
inoremap ' ''<ESC>i
inoremap ( ()<ESC>i

"����C����
set cin

"���ó�ʼ���ڴ�С
set lines=25 columns=100


"�趨�Ʊ����ȣ�
set tabstop=4
set softtabstop=4
"����(����)������ȣ�
set shiftwidth=4
"�����ļ����Զ�����
set autoindent

"���ý������ļ��Ĵ��Ŀ¼�������ļ�����ӣ�
set directory=D:\VimTemp
set noswapfile

"Ctags
set tags+=D:\Program%20Files\Vim\systags
set autochdir

syntax enable
syntax on

" ��ȡ��ǰĿ¼
func! GetPWD()
    return substitute(getcwd(), "", "", "g")
endf

" �Զ��ı䵱ǰĿ¼
if has('netbeans_intg')
    set autochdir
endif

" ��������״̬��
"set stl=\ \ [%{&fileformat},%{&fileencoding}]\ %w\ \ \ %r%{GetPWD()}%h\\%f\ %=\ %l/%L\ %=\[%P]


" �Զ����¶���
"set autoread
" �Զ����
set completeopt=longest,menu

let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

"taglist������
"���ڷ����ұ�
let Tlist_Use_Right_Window=0
"let Tlist_Show_Menu=1
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_Process_File_Always=1
"�����ʾ����Ŀ��
let Tlist_Max_Submenu_Items=100
"�����򿪶�Ӧ��tag
let Tlist_Use_SingleClick=1 
let Tlist_Auto_Update=1
let Tlist_Auto_Open=0

let NERDTreeMouseMode=1
let NERDTreeChDirMode=1

"let g:winManagerWindowLayout="NERDTree|TagList|BufExplorer"
let g:winManagerWindowLayout="NERDTree|TagList"
let g:winManagerWidth = 30
let g:defaultExplorer = 0

"����Ϊ�����Զ�����"
"�Զ��������� backup"
set nobackup

" �����python�ļ���ʹ�ÿո��滻tab��
autocmd FileType python set expandtab

"�½�������
nnoremap <silent> <F1> :enew<CR>
"ɾ��/�رյ�ǰ������
nnoremap <silent> <F2> :bdelete!<CR>
nnoremap <silent> <F9> :WMToggle<cr>
nnoremap <silent> <F11> :AV<CR>
nnoremap <silent> <F12> :A<CR>

map <F5> ms:call TitleDet()<cr>'s
function AddTitle()
    call append(0,"#-*- encoding: utf-8 -*-")
    call append(1,"#")
    call append(2,"# vim:    tabstop=4 shiftwidth=4 softtabstop=4")
    call append(3,"#")
    call append(4,"# Copyright @ 2012 AwCloud")
    call append(5,"#")
    call append(6,"# Author: zhangjl")
    call append(7,"#")
    call append(8,"# Email:  zhangjl@awcloud.com")
    call append(9,"#")
    call append(10,"# Licensed under the Apache License, Version 2.0 (the \"License\"); you may")
    call append(11,"# not use this file except in compliance with the License. You may obtain")
    call append(12,"# a copy of the License at")
    call append(13,"#")
    call append(14,"#      http://www.apache.org/licenses/LICENSE-2.0")
    call append(15,"#")
    call append(16,"# Unless required by applicable law or agreed to in writing, software")
    call append(17,"# distributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT")
    call append(18,"# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the")
    call append(19,"# License for the specific language governing permissions and limitations")
    call append(20,"# under the License.")
    call append(21,"#")
    call append(22,"#! /usr/bin/python")
    echohl WarningMsg | echo "Successful in adding the copyright." | echohl None
endf

function UpdateTitle()
    normal m'
    execute '/# *Last modified:/s@:.*$@\=strftime(":\t%Y-%m-%d %H:%M")@'
    normal ''
    normal mk
    execute '/# *Filename:/s@:.*$@\=":\t\t".expand("%:t")@'
    execute "noh"
    normal 'k
    echohl WarningMsg | echo "Successful in updating the copy right." | echohl None
endfunction
function TitleDet()
    let n=1
    while n < 10
        let line = getline(n)
        if line =~ '^\#\s*\S*Last\smodified:\S*.*$'
            call UpdateTitle()
            return
        endif
        let n = n + 1
    endwhile
    call AddTitle()
endfunction


map <F6> ms:call TitleDetForCAndJava()<cr>'s
function AddTitleForCAndJava()
    call append(0,"/*******************************************")
    call append(1,"#")
    call append(2,"# Author: ikaros")
    call append(3,"#")
    call append(4,"# Last modified: ".strftime("%Y-%m-%d %H:%M"))
    call append(5,"#")
    call append(6,"# Filename: ".expand("%:t"))
    call append(7,"#")
    call append(8,"******************************************/")
    echohl WarningMsg | echo "Successful in adding the copyright." | echohl None
endf

function UpdateTitleForCAndJava()
    normal m'
    execute '/# *Last modified:/s@:.*$@\=strftime(":\t%Y-%m-%d %H:%M")@'
    normal ''
    normal mk
    execute '/# *Filename:/s@:.*$@\=":\t\t".expand("%:t")@'
    execute "noh"
    normal 'k
    echohl WarningMsg | echo "Successful in updating the copy right." | echohl None
endfunction
function TitleDetForCAndJava()
    let n=1
    while n < 10
        let line = getline(n)
        if line =~ '^\#\s*\S*Last\smodified:\S*.*$'
            call UpdateTitle()
            return
        endif
        let n = n + 1
    endwhile
    call AddTitleForCAndJava()
endfunction
let g:pydiction_location = 'D:\Program Files\Vim\vimfiles\after\ftplugin\pydiction-1.2\complete-dict'
" ############### Gui��NoGui��ͳһ���� ���� ##################

" ############### Gui���� ��ʼ ##################
if has ("gui_running")
    "���ñ�����ɫ"
    color molokai
    " windows����������
    "exec 'set guifont='.iconv('DejaVu_Sans_Mono', &enc, 'utf-8').':h12'
    set gfn=DejaVu_Sans_Mono:h12:cANSI
    "set gfn=Courier_New:h12:cANSI
    "���ع�����
    set guioptions-=T
    " ��ʾ�������б�
    "let g:Tb_MoreThanOne = 1
    "ʼ����ʾ��ǩҳ��
    set showtabline=2
    "������ǰ��
    set cursorline
    "�б��
    "set cc=88
    set colorcolumn=88
    highlight ColorColumn guibg=#009ACD
    " ʼ����ʾ״̬��
    "set ls=2 
    "let g:indent_guides_start_level=1
    "let g:indent_guides_enable_on_vim_startup=1
    "let g:indent_guides_guide_size=1
    set laststatus=2
    "let g:Powerline_symbols = 'fancy'
    
    "let g:indentLine_enabled=0
    "let g:indentLine_loaded=1
    "let g:indentLine_color_gui = '#A4E57E'
    
    
    "let g:indent_guides_auto_colors = 0
    "autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=#B3EE3A
    "autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=#009ACD
" ############### Gui���� ���� ##################    
else
    color default
endif


