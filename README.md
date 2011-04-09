Aloha Editor for Drupal  
====================  
  
[aloha-editor.com](http://aloha-editor.com)  
[drupal.org](http://drupal.org)  
  
  
  
## Instructions to add Aloha Editor to Drupal (better 0.9 version. not stable)  
  
1.  Take a Drupal 7 / 6 installation.  
2.  Install the WYSIWYG module: [drupal.org page](http://drupal.org/project/wysiwyg) ([zip for 7.x](http://ftp.drupal.org/files/projects/wysiwyg-7.x-2.0.zip))  
3.  Download the Aloha Drupal - better 0.9 version. not stable: [current master zip-file](https://github.com/evo42/aloha-drupal/zipball/master)  
4.  Extract the .zip file and copy or better symlink:  
./aloha-drupal/alohaeditor to ./drupal_site/sites/all/libraries/alohaeditor  
./aloha-drupal/wysiwyg/editors/alohaeditor.inc to ./drupal_site/sites/all/modules/wysiwyg/editors/alohaeditor.inc  
./aloha-drupal/wysiwyg/editors/js/alohaeditor.js to ./drupal_site/sites/all/modules/wysiwyg/editors/js/alohaeditor.js  
5. To use the Aloha Drupal Link Lookup Service copy or symlink (optional):
./aloha-drupal/aloha-lookup.php to ./drupal_site/aloha-lookup.php
6. Edit this file and adjust your Drupal base URL if it is not 'http://host/' (if you use link lookup):
./drupal_site/sites/all/libraries/alohaeditor/aloha/plugins/com.gentics.aloha.plugins.Link/drupal.js: "GENTICS.Aloha.Repositories.drupal.settings.url"