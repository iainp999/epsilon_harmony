<?php

/**
 * @file
 * This file contains the admin section configurations form.
 */

module_load_include('inc', 'epsilon_harmony', 'includes/Api/EpsilonApiFactory');

/**
 * Implements hook_form().
 */
function epsilon_harmony_config_form($form, &$form_state) {
  $form['epsilon_harmony_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('Client ID for your Epsilon Harmony account.'),
    '#default_value' => variable_get('epsilon_harmony_client_id', ''),
    '#required' => TRUE,
  );

  $form['epsilon_harmony_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Key'),
    '#description' => t('Secret key for your Epsilon Harmony account.'),
    '#default_value' => variable_get('epsilon_harmony_secret_key', ''),
    '#required' => TRUE,
  );

  $form['epsilon_harmony_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('Username for your Epsilon Harmony account.'),
    '#default_value' => variable_get('epsilon_harmony_username', ''),
    '#required' => TRUE,
  );

  $form['epsilon_harmony_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('Password for your Epsilon Harmony account.'),
    '#default_value' => variable_get('epsilon_harmony_password', ''),
    '#required' => TRUE,
  );

  $form['epsilon_harmony_xouid'] = array(
    '#type' => 'textfield',
    '#title' => t('X-OUID'),
    '#description' => t('Enter the X-OUID key received from the Epsilon Harmony representative.'),
    '#default_value' => variable_get('epsilon_harmony_xouid', ''),
    '#required' => TRUE,
  );

  $form['epsilon_harmony_region'] = array(
    '#type' => 'radios',
    '#title' => t('Region'),
    '#options' => array(
      'eu' => t('Canada'),
      'us' => t('US'),
    ),
    '#description' => t('Enter the default region for the API.'),
    '#default_value' => variable_get('epsilon_harmony_region', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Implements hook_form().
 */
function epsilon_harmony_message_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  $initial_number = 0;

  if (empty($form_state['number_names'])) {
    $form_state['number_names'] = 1;
  }

  for ($i = 1; $i <= $form_state['number_names']; $i++) {
    $form['container'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Message'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['container'][$i]['name'] = array(
      '#type' => 'textfield',
      '#title' => "Message Identifier",
      '#required' => TRUE,
      '#disabled' => FALSE,
    );

    $form['container'][$i]['message_id'] = array(
      '#type' => 'textfield',
      '#title' => "Message ID",
      '#required' => TRUE,
    );
  }

  $message_id_array = variable_get('epsilon_harmony_message_id_array', '');
  $message_array = (array) json_decode($message_id_array);
  $min_field_count = count($message_array);

  $t = 1;
  foreach ($message_array as $key => $value) {
    $form['container'][$t] = array(
      '#type' => 'fieldset',
      '#title' => t('Message: @key', array('@key' => $key)),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['container'][$t]['name'] = array(
      '#type' => 'textfield',
      '#title' => "Message Identifier",
      '#required' => TRUE,
      '#disabled' => TRUE,
      '#default_value' => $key,
    );

    $form['container'][$t]['message_id'] = array(
      '#type' => 'textfield',
      '#title' => "Message ID",
      '#required' => TRUE,
      '#default_value' => $value,
    );
    $t++;
  }

  if ($min_field_count > $form_state['number_names']) {
    $form_state['number_names'] = $min_field_count;
  }

  $form['add_item'] = array(
    '#type' => 'submit',
    '#value' => t('Add another message ID'),
    '#submit' => array('epsilon_harmony_message_form_add_item'),
  );

  if ($form_state['number_names'] > 1) {
    $form['remove_item'] = array(
      '#type' => 'submit',
      '#value' => t('Remove last unsaved mesasge ID'),
      '#submit' => array('epsilon_harmony_message_form_remove_item'),
      // Since we are removing a name, don't validate until later.
      '#limit_validation_errors' => array(),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

/**
 * Add an option to create a new message ID.
 */
function epsilon_harmony_message_form_add_item($form, &$form_state) {
  // All we need is to increase the number used in our for loop above ...
  $form_state['number_names']++;
  // ... and rebuild our form.
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for `epsilon_harmony_message_form`.
 */
function epsilon_harmony_message_form_submit($form, &$form_state) {
  foreach ($form_state['values']['container'] as $key => $value) {
    $message_id_array[$value['name']] = $value['message_id'];
  }
  if(!empty($message_id_array)) {
    variable_set('epsilon_harmony_message_id_array', json_encode($message_id_array));
    return TRUE;
  }
  return FALSE;
}

/**
 * Delete the last unsaved message ID.
 */
function epsilon_harmony_message_form_remove_item($form, &$form_state) {
  // Remove the last unsaved message ID.
  if ($form_state['number_names'] > 1) {
    $form_state['number_names']--;
  }
  // ... and form rebuild again.
  $form_state['rebuild'] = TRUE;
}
