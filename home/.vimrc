set nocompatible                  " Must come first because it changes other options.
syntax enable                     " Turn on syntax highlighting.
filetype plugin on                " Turn on file type detection.
set showcmd                       " Display incomplete commands.
set showmode                      " Display the mode you're in.
set backspace=indent,eol,start    " Intuitive backspacing.
set hidden                        " Handle multiple buffers better.
set wildmenu                      " Enhanced command line completion.
set wildmode=list:longest         " Complete files like a shell.
set incsearch                     " Highlight matches as you type.
set hlsearch                      " Highlight matches.
set wrap                          " Turn on line wrapping.
set tabstop=2                     " Global tab width.
set shiftwidth=2                  " And again, related.
set modeline                      " Allow per file config
set expandtab
set ruler
set background=dark
set autoindent
colorscheme candycode
command W w!
command Wq wq!
command Q q

