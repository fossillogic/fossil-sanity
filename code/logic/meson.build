dir = include_directories('.')

sanity_code = ['sanity.c']

fossil_sanity_lib = library('fossil-sanity',
    sanity_code,
    install: true,
    include_directories: dir)

fossil_sanity_dep = declare_dependency(
    link_with: fossil_sanity_lib,
    include_directories: dir)
