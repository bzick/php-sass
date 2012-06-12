PHP SASS extension
========

Installation:

    mkdir /tmp/php-sass
    git clone https://github.com/bzick/php-sass.git /tmp/php-sass
    cd /tmp/php-sass
    sudo ./install.sh
    # or 
    sudo ./checkinstall.sh
    
See install.sh or checkinstall.sh for more information


Usage
-----
See https://github.com/bzick/php-sass/blob/master/sass.php


Elements of the extension
-----
`SASS` main class

`SASS::VERSION_NUMBER` integer constant

`SASS::STYLE_NESTED` integer constant

`SASS::STYLE_EXPANDED` integer constant **not implemented in libsass**

`SASS::STYLE_COMPACT` integer constant **not implemented in libsass**

`SASS::STYLE_COMPRESSED` integer constant **not implemented in libsass**

`SASS::compile()` method, return string

`SASS::compileFile()` method, return string

`SASS::compileFolder()` method **not implemented**

`SASS\CompileErrorException` exception class

Also, argument `$include_paths` **not implemented**