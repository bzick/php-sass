--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compileFile(__DIR__."/file1.sass", SASS::STYLE_NESTED);
?>
--EXPECT--
div a {
  color: black; }