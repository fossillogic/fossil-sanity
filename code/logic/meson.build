dir = include_directories('.')
cc = meson.get_compiler('c')

sanity_code = ['sanity.c', 'validate.c', 'parser.c']

fossil_sanity_lib = library('fossil-sanity',
    sanity_code,
    install: true,
    dependencies: cc.find_library('m', required : false),
    include_directories: dir)

fossil_sanity_dep = declare_dependency(
    link_with: fossil_sanity_lib,
    include_directories: dir)
