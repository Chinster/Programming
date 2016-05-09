" Vundle setup
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'rust-lang/rust.vim'
Plugin 'scrooloose/syntastic'

call vundle#end()
filetype indent plugin on

" Expected editor options
set wildmenu
set hlsearch
set ignorecase   " Case-insensitive search
set smartcase    " Case-sensitive search when capitalized
set visualbell
set number
syntax on        " Syntax coloring
set t_Co=256     " Number of colors
set iskeyword-=_ " Allows _ to seperate words

" Spacing options
set shiftwidth=4
set softtabstop=4
set expandtab

" File-specific spacing
autocmd FileType html setlocal shiftwidth=2 tabstop=2
autocmd FileType css setlocal shiftwidth=2 tabstop=2

" Syntax highlighting
au BufRead,BufNewFile *.pde set filetype=arduino
au BufRead,BufNewFile *.ino set filetype=arduino

" Quality of life options
set colorcolumn=80 " Highlight column 80
set cursorline     " Underline current line

" Code folding
set foldmethod=indent
set foldnestmax=1
set foldlevel=1

set tags=./tags                     " Ctags
cmap w!! w !sudo tee > /dev/null %  " Save file as sudo
