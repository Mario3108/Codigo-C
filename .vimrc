set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'dracula/vim', { 'name': 'dracula' }
Plugin 'jiangmiao/auto-pairs'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
"Plugin 'file:///home/gmarik/path/to/plugin'

" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

syntax enable
colorscheme dracula
set number
set backspace=2
set laststatus=2
set expandtab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set list
set listchars=tab:>-,trail:•,extends:#,nbsp:.
set pastetoggle=<F12>
set hlsearch
"set completeopt-=preview
set wildmode=longest,list,full
set wildmenu
set showcmd
set ignorecase
set smartcase
set ttimeoutlen=0
set foldmethod=manual
set autoread
set viminfo='100,<1000,s100,:100,n$HOME/.vim/viminfo
set colorcolumn=80

autocmd BufNewFile,BufRead *.md filetype plugin indent off

let g:ycm_confirm_extra_conf=0
let g:rainbow_active=1

" Persistant Undo
set undofile
set undodir=$HOME/.vimundo
set undolevels=1000
set undoreload=10000

" Markdown preview testing
let g:instant_markdown_open_to_the_world=1


" Para la barra de abajo del todo
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'
let g:airline#extensions#tabline#formatter = 'default'


nnoremap <F5> :YcmForceCompileAndDiagnostics<CR>
nnoremap <C-G> :YcmCompleter GoTo<CR>
nnoremap <F2> :set foldmethod=indent<CR>
nnoremap <F3> :NERDTree<CR>
nnoremap <F4> :UndotreeToggle<CR>
noremap j gj
noremap k gk
map /  <Plug>(incsearch-forward)
map ?  <Plug>(incsearch-backward)
map g/ <Plug>(incsearch-stay)
nnoremap gr :!grep -rniIw --color=auto "<cword>" .<CR>
nnoremap gR :!grep -rniI --color=auto "<cword>" .<CR>
nnoremap Q <NOP>
nnoremap <F9> :SLoad<SPACE>
cabbrev h vert h

if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

highlight Pmenu ctermbg=0

fun! ShowFuncName()
  let lnum = line(".")
  let col = col(".")
  echohl ModeMsg
  echo getline(search("^[^ \t#/]\\{2}.*[^:]\s*$", 'bW'))
  echohl None
  call search("\\%" . lnum . "l" . "\\%" . col . "c")
endfun
map f :call ShowFuncName() <CR>

abbreviate ffia from __future__ import division<CR>from __future__ import absolute_import<CR>from __future__ import print_function<CR>from __future__ import unicode_literals

" Crontab requires that files are edited in place
au FileType crontab setlocal bkc=yes

map <F10> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<'
\ . synIDattr(synID(line("."),col("."),0),"name") . "> lo<"
\ . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>

" Disable rainbow in html.jinja
au FileType jinja.html RainbowToggle


