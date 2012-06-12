--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
    try {
        echo SASS::compile('div ---', SASS::STYLE_NESTED);
    } catch(SASS\CompileErrorException $e) {
        echo "Error occurred";
    }
?>
--EXPECT--
Error occurred