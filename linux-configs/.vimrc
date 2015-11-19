set nocompatible

" Better command-line completion
set wildmode=longest,list,full
set wildmenu

" Show partial commands in the last line of the screen
set showcmd

" Highlight searches (use <C-L> to temporarily turn off highlighting; see the
" mapping of <C-L> below)
set hlsearch

" Use case insensitive search, except when using capital letters
set ignorecase
set smartcase

" Enable syntax highlighting
syntax on

" When opening a new line and no filetype-specific indenting is enabled, keep
" the same indent as the line you're currently on. Useful for READMEs, etc.
set autoindent

" Instead of failing a command because of unsaved changes, instead raise a
" dialogue asking if you wish to save changed files.
set confirm

" Use visual bell instead of beeping when doing something wrong
set visualbell

" Display line numbers on the left
set number

" spaces per indent.
set shiftwidth=4
set softtabstop=4

" This converts tabs to spaces
set expandtab

" correct backspace key
set backspace=indent,eol,start

" Relative line nubmering
set relativenumber

<<<<<<< 70edb3302fbe898a75ddac5cb4224bc6e8b4470c
=======
" Highlights column 80
>>>>>>> init commit from private repo migration
set colorcolumn=80
set cursorline

" Makes things colorful
set t_Co=16

" Save file as sudo
cmap w!! w !sudo tee > /dev/null %

" Reduce indent size for these filetypes
autocmd FileType html setlocal shiftwidth=2 tabstop=2
autocmd FileType css setlocal shiftwidth=2 tabstop=2

" Syntax highlighting for arduino files.
au BufRead,BufNewFile *.pde set filetype=arduino
au BufRead,BufNewFile *.ino set filetype=arduino
" <Leader> maps to mapleader variable
let mapleader = ","

" Vim/Vundle plugins below
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'rust-lang/rust.vim'
Plugin 'scrooloose/syntastic'

call vundle#end()
filetype indent plugin on
