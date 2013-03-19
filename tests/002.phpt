--TEST--
Test skeetr_override_function
--FILE--
<?php 
skeetr_override_function('var_dump', '', 'return "works";');
echo var_dump();
--EXPECT--
works