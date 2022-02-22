TEMPLATE = app
TARGET = scl-meta-test-detection
CONFIG *= console

DEPENDS *= \
    scl-meta \

!load( include_files ) : error( Can not find feature \"include_files\" )
includeFiles( $${PWD}/../../../../test/Detection )
