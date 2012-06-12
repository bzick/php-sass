--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compile(
'$blue: #3bbfce;
$margin: 16px;

.content-navigation {
  border-color: $blue;
  color:
    darken($blue, 9%);
}

.border {
  padding: $margin / 2;
  margin: $margin / 2;
  border-color: $blue;
}',
  SASS::STYLE_NESTED);
?>
--EXPECT--
.content-navigation {
  border-color: #3bbfce;
  color: darken($blue, 9%); }

.border {
  padding: 8px;
  margin: 8px;
  border-color: #3bbfce; }