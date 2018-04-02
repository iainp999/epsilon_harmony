<?php

/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_default_views().
 */
function epsilon_harmony_views_default_views() {
  $view = new view();
  $view->name = 'epsilon_harmony_logs';
  $view->description = 'Access the log entry for all the epsilon API requests.';
  $view->tag = 'default';
  $view->base_table = 'epsilon_harmony_logs';
  $view->human_name = 'Epsilon Harmony Logs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Epsilon Harmony API Logs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access epsilon harmony logs';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'log_id' => 'log_id',
    'created' => 'created',
    'data' => 'data',
    'log_id_1' => 'log_id_1',
    'status_code' => 'status_code',
    'status_message' => 'status_message',
    'url' => 'url',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'log_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'data' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'log_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'url' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2>No data</h2>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Epsilon Harmony Logs: Epsilon harmony logs ID */
  $handler->display->display_options['fields']['log_id']['id'] = 'log_id';
  $handler->display->display_options['fields']['log_id']['table'] = 'epsilon_harmony_logs';
  $handler->display->display_options['fields']['log_id']['field'] = 'log_id';
  $handler->display->display_options['fields']['log_id']['label'] = 'ID';
  $handler->display->display_options['fields']['log_id']['separator'] = '';
  /* Field: Epsilon Harmony Logs: Endpoint */
  $handler->display->display_options['fields']['endpoint']['id'] = 'endpoint';
  $handler->display->display_options['fields']['endpoint']['table'] = 'epsilon_harmony_logs';
  $handler->display->display_options['fields']['endpoint']['field'] = 'endpoint';
  /* Field: Epsilon Harmony Logs: Status_code */
  $handler->display->display_options['fields']['status_code']['id'] = 'status_code';
  $handler->display->display_options['fields']['status_code']['table'] = 'epsilon_harmony_logs';
  $handler->display->display_options['fields']['status_code']['field'] = 'status_code';
  $handler->display->display_options['fields']['status_code']['label'] = 'Status Code';
  $handler->display->display_options['fields']['status_code']['separator'] = '';
  /* Field: Epsilon Harmony Logs: Status_message */
  $handler->display->display_options['fields']['status_message']['id'] = 'status_message';
  $handler->display->display_options['fields']['status_message']['table'] = 'epsilon_harmony_logs';
  $handler->display->display_options['fields']['status_message']['field'] = 'status_message';
  $handler->display->display_options['fields']['status_message']['label'] = 'Status Message';
  /* Field: Epsilon Harmony Logs: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'epsilon_harmony_logs';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Epsilon Harmony Logs: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'views_entity_epsilon_harmony_logs';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['label'] = 'Details';
  $handler->display->display_options['fields']['url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['url']['alter']['text'] = '<a href=[url]>Link</a>';
  $handler->display->display_options['fields']['url']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['url']['link_to_entity'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['display_description'] = 'Access the log entry for all the epsilon API requests.';
  $handler->display->display_options['path'] = 'admin/config/services/epsilon_harmony/logs';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Epsilon Harmony Logs';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;
  return $views;
}
