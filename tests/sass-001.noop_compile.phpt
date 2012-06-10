--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compile(
"* {
  color: red;
  float: left; }"
	);
?>
--EXPECT--
* {
  color: red;
  float: left; }