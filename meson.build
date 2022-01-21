project('libge', 'c')

install_headers('libge.h')
libge = library('ge', 'libge.c')

executable('demo', 'demo.c', link_with : libge)
