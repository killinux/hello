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

" ############### Gui和NoGui的统一设置 开始 ##################
"解决菜单乱码（包括gvim和命令行模式下）
set nocompatible
set backspace=2

source $VIMRUNTIME/vimrc_example.vim
if has('win32')
    source $VIMRUNTIME/mswin.vim
    behave mswin
endif

" 文件编码和文件的字符集
let &termencoding=&encoding
set fileformat=unix
set fileformats=unix
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set fileencoding=utf-8 " 新建文件使用的编码
set langmenu=zh_CN
let $LANG = 'zh_CN.UTF-8'
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim

"文件类型检测, 加了这句才可以用智能补全
filetype on
filetype plugin on
filetype indent on

"显示行号
set nu!
"set ruler

"Vim 中实现括号与引号以及<>的自动补全"
inoremap [ []<ESC>i
inoremap { {}<ESC>i
inoremap < <><ESC>i
inoremap " ""<ESC>i
inoremap ' ''<ESC>i
inoremap ( ()<ESC>i

"设置C缩进
set cin

"设置初始窗口大小
set lines=25 columns=100


"设定制表符宽度：
set tabstop=4
set softtabstop=4
"设置(行首)缩进宽度：
set shiftwidth=4
"设置文件的自动缩进
set autoindent

"设置交换区文件的存放目录：配置文件中添加：
set directory=D:\VimTemp
set noswapfile

"Ctags
set tags+=D:\Program%20Files\Vim\systags
set autochdir

syntax enable
syntax on

" 获取当前目录
func! GetPWD()
    return substitute(getcwd(), "", "", "g")
endf

" 自动改变当前目录
if has('netbeans_intg')
    set autochdir
endif

" 命令行于状态行
"set stl=\ \ [%{&fileformat},%{&fileencoding}]\ %w\ \ \ %r%{GetPWD()}%h\\%f\ %=\ %l/%L\ %=\[%P]


" 自动重新读入
"set autoread
" 自动完成
set completeopt=longest,menu

let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

"taglist的设置
"窗口放于右边
let Tlist_Use_Right_Window=0
"let Tlist_Show_Menu=1
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_Process_File_Always=1
"最多显示的条目数
let Tlist_Max_Submenu_Items=100
"单击打开对应的tag
let Tlist_Use_SingleClick=1 
let Tlist_Auto_Update=1
let Tlist_Auto_Open=0

let NERDTreeMouseMode=1
let NERDTreeChDirMode=1

"let g:winManagerWindowLayout="NERDTree|TagList|BufExplorer"
let g:winManagerWindowLayout="NERDTree|TagList"
let g:winManagerWidth = 30
let g:defaultExplorer = 0

"设置为不是自动备份"
"自动备份则是 backup"
set nobackup

" 如果是python文件，使用空格替换tab键
autocmd FileType python set expandtab

"新建缓冲区
nnoremap <silent> <F1> :enew<CR>
"删除/关闭当前缓冲区
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
" ############### Gui和NoGui的统一设置 结束 ##################

" ############### Gui设置 开始 ##################
if has ("gui_running")
    "设置背景颜色"
    color molokai
    " windows下设置字体
    "exec 'set guifont='.iconv('DejaVu_Sans_Mono', &enc, 'utf-8').':h12'
    set gfn=DejaVu_Sans_Mono:h12:cANSI
    "set gfn=Courier_New:h12:cANSI
    "隐藏工具栏
    set guioptions-=T
    " 显示缓冲区列表
    "let g:Tb_MoreThanOne = 1
    "始终显示标签页：
    set showtabline=2
    "高亮当前行
    set cursorline
    "列标尺
    "set cc=88
    set colorcolumn=88
    highlight ColorColumn guibg=#009ACD
    " 始终显示状态行
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
" ############### Gui设置 结束 ##################    
else
    color default
endif


