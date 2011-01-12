<?php
/**
* use drupal search for the aloha link suggestion plugin
*/
// DEBUG
//error_log(print_r($_REQUEST, true), 3, "aloha.log");

$lookup = $_REQUEST['lookup'];

define('DRUPAL_ROOT', getcwd());

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

$search_results = node_search_execute($lookup);
//error_log(print_r($search_results, true), 3, "aloha.log");

header('Content-Type:text/javascript');
if (is_array($search_results[0])) {
$out = '[';
foreach ($search_results as $result) {
$out .= '{"u":"'.$result['link'].'","d":"'.$result['title'].'","a":"","t":[""],"dt":"2009-05-18T15:32:30Z","n":""},';
}
$out = substr($out, 0, -1);
$out .= ']';
echo $out;
}