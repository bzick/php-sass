--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compile(
"* {
  color: red;
  float: left; }",
  SASS::STYLE_NESTED);
?>
--EXPECT--
* {
  color: red;
  float: left; }