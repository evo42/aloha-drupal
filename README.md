Aloha Editor for Drupal
====================

http://aloha-editor.com
http://drupal.org



## Instructions to add Aloha Editor to Drupal (better 0.9 version. not stable)

Take a Drupal 7 / 6 installation.
Install the WYSIWYG module: http://drupal.org/project/wysiwyg -- http://ftp.drupal.org/files/projects/wysiwyg-7.x-2.0.zip
Download the Aloha Drupal - better 0.9 version. not stable. - code: https://github.com/evo42/aloha-drupal/zipball/master
Extract the .zip file and copy or better symlink:
./aloha-drupal/alohaeditor to ./drupal_site/sites/all/libraries/alohaeditor
./aloha-drupal/wysiwyg/editors/alohaeditor.inc to ./drupal_site/sites/all/modules/wysiwyg/editors/alohaeditor.inc
./aloha-drupal/wysiwyg/editors/js/alohaeditor.js to ./drupal_site/sites/all/modules/wysiwyg/editors/js/alohaeditor.js



To use the Aloha Drupal Link Lookup Service copy or symlink (optional):
./aloha-drupal/aloha-lookup.php to ./drupal_site/aloha-lookup.php

Edit this file and adjust your Drupal base URL if it is not 'http://host/' (if you use link lookup):
./drupal_site/sites/all/libraries/alohaeditor/aloha/plugins/com.gentics.aloha.plugins.Link/drupal.js: "GENTICS.Aloha.Repositories.drupal.settings.url"