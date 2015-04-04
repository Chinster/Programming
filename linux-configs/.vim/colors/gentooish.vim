" Vim color file
" Name:    gentooish.vim
" Author:  Brian Carper<brian@briancarper.net>, higher color contrast by
" Christopher Chin
" Version: 0.3

set background=dark
hi clear
if exists("syntax_on")
   syntax reset
endif

" Dumped via CSApprox, then edited slightly
" (http://www.vim.org/scripts/script.php?script_id=2390)
hi SpecialKey     term=bold ctermfg=58
hi NonText        term=bold ctermfg=240
hi Directory      term=bold ctermfg=120
hi ErrorMsg       term=standout ctermfg=255 ctermbg=132
hi Search         term=reverse ctermfg=119 ctermbg=16
hi IncSearch      term=reverse ctermfg=132 ctermbg=255
hi MoreMsg        term=bold ctermfg=255
hi ModeMsg        term=bold ctermfg=255
hi LineNr         term=underline ctermfg=252 ctermbg=235
hi Question       term=standout ctermfg=255
hi StatusLine     term=bold,reverse cterm=bold ctermfg=255 ctermbg=236
hi StatusLineNC   term=reverse cterm=bold ctermfg=240 ctermbg=236
hi VertSplit      term=reverse ctermfg=255 ctermbg=236
hi Title          term=bold ctermfg=132
hi Visual         term=reverse ctermfg=255 ctermbg=60
hi VisualNOS      term=bold,underline ctermfg=255 ctermbg=16
hi WarningMsg     term=standout ctermfg=255 ctermbg=132
hi WildMenu       term=standout cterm=bold ctermfg=199 ctermbg=16
hi Folded         term=standout ctermfg=142 ctermbg=16
hi FoldColumn     term=standout ctermfg=255 ctermbg=16
hi DiffAdd        term=bold ctermfg=255 ctermbg=59
hi DiffChange     term=bold ctermbg=54
hi DiffDelete     term=bold ctermfg=255 ctermbg=132
hi DiffText       term=reverse ctermfg=16 ctermbg=154
hi SignColumn     term=standout ctermfg=51 ctermbg=252
hi TabLine        term=underline cterm=underline ctermbg=250
hi TabLineSel     term=bold cterm=bold
hi TabLineFill    term=reverse ctermfg=234 ctermbg=255
hi CursorColumn   term=reverse ctermbg=235
hi CursorLine     term=underline ctermbg=235
hi Cursor         ctermfg=16 ctermbg=120
hi lCursor        ctermfg=234 ctermbg=255
hi Normal         ctermfg=255 ctermbg=234
hi Comment        term=bold ctermfg=241
hi Constant       term=underline ctermfg=142
hi Special        term=bold ctermfg=222
hi Identifier     term=underline ctermfg=74
hi Statement      term=bold ctermfg=154
hi PreProc        term=underline ctermfg=132
hi Type           term=underline ctermfg=199
hi Underlined     term=underline cterm=underline ctermfg=255
hi Ignore         ctermfg=240
hi Error          term=reverse ctermfg=88 ctermbg=16
hi Todo           term=standout ctermfg=255 ctermbg=132
hi String         ctermfg=83 ctermbg=234
hi Number         ctermfg=178
hi Boolean        ctermfg=46
hi User1          cterm=bold ctermfg=246 ctermbg=236
hi User2          cterm=bold ctermfg=120 ctermbg=236
if v:version >= 700
    hi SpellBad       term=reverse cterm=undercurl ctermfg=167
    hi SpellCap       term=reverse cterm=undercurl ctermfg=80
    hi SpellRare      term=reverse cterm=undercurl ctermfg=170
    hi SpellLocal     term=underline cterm=undercurl ctermfg=185
    hi Pmenu          ctermfg=255 ctermbg=235
    hi PmenuSel       cterm=bold ctermfg=199 ctermbg=16
    hi PmenuSbar      ctermfg=255 ctermbg=16
    hi PmenuThumb     ctermfg=255 ctermbg=236
    hi MatchParen     term=reverse ctermfg=231 ctermbg=22
endif
