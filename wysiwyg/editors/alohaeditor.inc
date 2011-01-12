<?php
/**
 * @file
 * Editor integration functions for Aloha Editor.
 */

/**
 * Plugin implementation of hook_editor().
 */
function wysiwyg_alohaeditor_editor() {

drupal_add_js("jQuery(document).ready(function () { 

/* Check if base DIR is set through configuration otherwise set to default */

	if (typeof GENTICS_Aloha_base == 'undefined') {
			 GENTICS_Aloha_base = Drupal.settings.basePath + 'sites/all/libraries/alohaeditor/aloha/'; 
	}
	});",
    array('type' => 'inline', 'scope' => 'header', 'weight' => 5)
    );

  $editor['alohaeditor'] = array(
    'title' => 'Aloha Editor',
    'vendor url' => 'http://www.aloha-editor.com/',
    'download url' => 'https://github.com/alohaeditor/Aloha-Editor',
    'library path' => wysiwyg_get_path('alohaeditor') . '/aloha',
    'libraries' => array(
      'min' => array(
        'title' => 'Minified',
        'files' => array('aloha.js',
        					'aloha-extras.js',
        					// plugins
        					'plugins/com.gentics.aloha.plugins.Format/plugin.js',
        					'plugins/com.gentics.aloha.plugins.Table/plugin.js',
        					'plugins/com.gentics.aloha.plugins.List/plugin.js',
        					'plugins/com.gentics.aloha.plugins.Link/plugin.js',
        					'plugins/com.gentics.aloha.plugins.HighlightEditables/plugin.js',
        					'plugins/com.gentics.aloha.plugins.TOC/plugin.js',
        					//'plugins/com.gentics.aloha.plugins.Link/delicious.js',
        					'plugins/com.gentics.aloha.plugins.Link/drupal.js',
        					'plugins/com.gentics.aloha.plugins.Link/LinkList.js',
        					'plugins/com.gentics.aloha.plugins.Paste/plugin.js',
        					'plugins/com.gentics.aloha.plugins.Paste/wordpastehandler.js',
        					),
      ),
      /*'pack' => array(
        'title' => 'Packed',
        'files' => array(),
      ),
      'src' => array(
        'title' => 'Source',
        'files' => array('include.js'),
      ),*/
    ),
    'version callback' => 'wysiwyg_alohaeditor_version',
    'themes callback' => 'wysiwyg_alohaeditor_themes',
    'settings callback' => 'wysiwyg_alohaeditor_settings',
    'plugin callback' => 'wysiwyg_alohaeditor_plugins',
    'versions' => array(
      'nightly' => array(
        'js files' => array('alohaeditor.js'),
      ),
    ),
  );
  return $editor;
}

/**
 * Detect editor version.
 *
 * @param $editor
 *   An array containing editor properties as returned from hook_editor().
 *
 * @return
 *   The installed editor version.
 */
function wysiwyg_alohaeditor_version($editor) {
  $script = $editor['library path'] . '/VERSION.txt';
  if (!file_exists($script)) {
    return;
  }
  $script = fopen($script, 'r');
  fgets($script);
  $line = fgets($script);
  if (preg_match('([0-9a-zA-Z\.-]+)', $line, $version)) {
    fclose($script);
    return $version[0];
  }
  fclose($script);
}

/**
 * Determine available editor themes or check/reset a given one.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $profile
 *   A wysiwyg editor profile.
 *
 * @return
 *   An array of theme names. The first returned name should be the default
 *   theme name.
 */
function wysiwyg_alohaeditor_themes($editor, $profile) {
  return array('default');
  //return array('compact', 'default', 'minimal', 'silver', 'twopanels');
}

/**
 * Return runtime editor settings for a given wysiwyg profile.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $config
 *   An array containing wysiwyg editor profile settings.
 * @param $theme
 *   The name of a theme/GUI/skin to use.
 *
 * @return
 *   A settings array to be populated in
 *   Drupal.settings.wysiwyg.configs.{editor}
 */
function wysiwyg_alohaeditor_settings($editor, $config, $theme) {
  // @todo Setup $library in wysiwyg_load_editor() already.
  $library = (isset($editor['library']) ? $editor['library'] : key($editor['libraries']));
  $settings = array(
    'basePath' => base_path() . $editor['library path'] . '/',
    //'wymPath' => $editor['libraries'][$library]['files'][0],
    // @todo Does not work in Drupal; jQuery can live anywhere.
    'jQueryPath' => base_path() . 'misc/jquery.js',
    'updateSelector' => '.form-submit',
    'skin' => $theme,
  );

  if (isset($config['language'])) {
    $settings['lang'] = $config['language'];
  }

  // Add configured buttons.
  $settings['toolsItems'] = array();
  if (!empty($config['buttons'])) {
    $buttoninfo = _wysiwyg_alohaeditor_button_info();
    $plugins = wysiwyg_get_plugins($editor['name']);
    foreach ($config['buttons'] as $plugin => $buttons) {
      foreach ($buttons as $button => $enabled) {
        // Iterate separately over buttons and extensions properties.
        foreach (array('buttons', 'extensions') as $type) {
          // Skip unavailable plugins.
          if (!isset($plugins[$plugin][$type][$button])) {
            continue;
          }
          // Add buttons.
          if ($type == 'buttons') {
            // Merge meta-data for internal default buttons.
            if (isset($buttoninfo[$button])) {
              //$buttoninfo[$button] += array('name' => $button);
              //$settings['toolsItems'][] = $buttoninfo[$button];
            }
            // For custom buttons, try to provide a valid button definition.
            else {
              /*$settings['toolsItems'][] = array(
                'name' => $button,
                'title' => $plugins[$plugin][$type][$button],
                'css' => 'wym_tools_' . $button,
              );*/
            }
          }
        }
      }
    }
  }

  if (!empty($config['block_formats'])) {
    $containers = array(
      'p' => 'Paragraph',
      'h1' => 'Heading_1',
      'h2' => 'Heading_2',
      'h3' => 'Heading_3',
      'h4' => 'Heading_4',
      'h5' => 'Heading_5',
      'h6' => 'Heading_6',
      'pre' => 'Preformatted',
      'blockquote' => 'Blockquote',
      'th' => 'Table_Header',
    );
    foreach (explode(',', $config['block_formats']) as $tag) {
      if (isset($containers[$tag])) {
        // @todo
        /*$settings['containersItems'][] = array(
          'name' => strtoupper($tag),
          'title' => $containers[$tag],
          'css' => 'xy_' . $tag,
        );*/
      }
    }
  }

  if (isset($config['css_setting'])) {
    if ($config['css_setting'] == 'theme') {
      // @todo
      //$settings['stylesheet'] = reset(wysiwyg_get_css());
    }
    else if ($config['css_setting'] == 'self' && isset($config['css_path'])) {
      $settings['stylesheet'] = strtr($config['css_path'], array('%b' => base_path(), '%t' => path_to_theme()));
    }
  }

  return $settings;
}

/**
 * Return internal plugins for this editor; semi-implementation of hook_wysiwyg_plugin().
 */
function wysiwyg_alohaeditor_plugins($editor) {
  $plugins = array(
    'default' => array(
      'buttons' => array(
        // @todo
        /*
        'Bold' => t('Bold'), 'Italic' => t('Italic'),
        'Preview' => t('Preview'),*/
      ),
      'internal' => TRUE,
    ),
  );
  return $plugins;
}

/**
 * Helper function to provide additional meta-data for internal default buttons.
 */
function _wysiwyg_alohaeditor_button_info() {
  return array(
     // @todo
        /*'Bold' => array('title'=> 'Strong', 'css'=> 'wym_tools_strong'),
    'ToggleHtml' => array('title'=> 'HTML', 'css'=> 'wym_tools_html'),
    'Preview' => array('title'=> 'Preview', 'css'=> 'wym_tools_preview'),
    */
  );
}
