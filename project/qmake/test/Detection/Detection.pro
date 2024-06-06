TEMPLATE = app
TARGET = scl-meta-test-detection
CONFIG *= console

DEPENDS *= \
    scl-meta \

!load( include_files ) : error( Can not find feature \"include_files\" )
!load( module_depends ) : error( Can not find feature \"module_depends\" )

includeFiles( $${PWD}/../../../../test/Detection )
