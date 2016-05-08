set nocompatible

" Vundle setup filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'rust-lang/rust.vim'
Plugin 'scrooloose/syntastic'

call vundle#end()
filetype indent plugin on

" Better command-line completion
set wildmenu
set showcmd

set hlsearch
" Case insensitive search
set ignorecase
set smartcase

set visualbell
set number

" 4 spaces.
set shiftwidth=4
set softtabstop=4
set expandtab

" Change whitespace size fo certain files
autocmd FileType html setlocal shiftwidth=2 tabstop=2
autocmd FileType css setlocal shiftwidth=2 tabstop=2

" correct backspace key
set backspace=indent,eol,start
syntax on
set nowrap
set t_Co=256

" Allows _ to seperate words
set iskeyword-=_

" Highlights column 80
set colorcolumn=80
set cursorline

" Prevent EOL at EOF
" set binary
" au BufNewFile * set noeol

" Code folding
set foldmethod=indent
set foldnestmax=1
set foldlevel=1

" Save file as sudo
cmap w!! w !sudo tee > /dev/null %

" Syntax highlighting for arduino files.
au BufRead,BufNewFile *.pde set  filetype=arduino
au BufRead,BufNewFile *.ino set  filetype=arduino

" <Leader> maps to mapleader variable
let mapleader = ","
