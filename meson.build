project('libge', 'c')

install_headers('libge.h')
libge = library('ge', 'libge.c', install: true)

pkg = import('pkgconfig')
pkg.generate(libge, version : '0.0', filebase : 'libge')

executable('demo', 'demo.c', link_with : libge)
