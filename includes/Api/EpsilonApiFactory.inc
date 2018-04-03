<?php

namespace Drupal\epsilon_harmony;
module_load_include('inc', 'epsilon_harmony', 'includes/Api/EpsilonConnectionFactory');

use Exception as Exception;

/**
 * Description for API Factory of Harmony API.
 *
 * @author Darshan Choudhary
 */
class EpsilonApiFactory extends EpsilonHarmonyConnectorFactory {

  /**
   * Get a new access token or an existing one for the API.
   *
   * @return string
   *   Returns the access token.
   */
  public static function getToken($object, $test = FALSE) {
    // @todo Check if the timeout is set to 3600
    if ($test == TRUE || ($object->getTokenTimeout() == NULL || (time() - $object->getTokenTimeout() > 3600))) {
      $url = "https://api-public.eu.epsilon.com/Epsilon/oauth2/access_token";

      // Form data to be passed.
      $data['username']   = $object->getUsername();
      $data['password']   = $object->getPassword();
      $data['scope']      = 'cn mail sn givenname uid employeeNumber';
      $data['grant_type'] = 'password';

      $options = array(
        'method' => 'POST',
        'headers' => array(
          'Authorization' => 'Basic ' . $object->getBaseToken(),
          'Content-Type' => 'application/x-www-form-urlencoded',
        ),
        'data' => $object->serializeData($data),
      );

      // HTTP Form request.
      $request = drupal_http_request($url, $options);

      // Log the API.
      $logArr['endpoint'] = $url;
      $logArr['status_code'] = (isset($request->code)) ? $request->code : "";
      $logArr['status_message'] = (isset($request->status_message)) ? $request->status_message : "";
      $logArr['header'] = json_encode($options['headers']);
      $logArr['request'] = json_encode($options['data']);
      $logArr['response'] = (isset($request->data)) ? $request->data : $request->error;
      epsilon_harmony_log($logArr);

      if ($request->code == 200) {
        variable_set('epsilon_harmony_token_timeout', time());
        variable_set('epsilon_harmony_access_token', json_decode($request->data)->access_token);
        return json_decode($request->data)->access_token;
      }
      else {
        throw new Exception('Something went wrong while fetching the token. Please check the logs for further details.');
      }
    }
    else {
      return self::$accessToken;
    }
  }

  /**
   * Created a record on Epsilon DB by calling the API.
   *
   * @param array $record
   *   Data to be passed through API.
   *
   * @return array
   *   Returns the response recieved from the API.
   */
  public function createRecord($record) {
    try {
      $url = "https://api.harmony.eu.epsilon.com/v4/profiles/records";
      $record = json_encode($record);
      $options = array(
        'method' => 'POST',
        'headers' => array(
          'Authorization' => 'Bearer ' . self::getToken($this),
          'X-OUID' => $this->getXouid(),
          'Content-Type' => 'application/json',
        ),
        'data' => $record,
      );

      // HTTP Form request.
      $request = drupal_http_request($url, $options);

      // Log the API.
      $logArr['endpoint'] = $url;
      $logArr['header'] = json_encode($options['headers']);
      $logArr['request'] = json_encode($options['data']);
      $logArr['status_code'] = (isset($request->code)) ? $request->code : "";
      $logArr['status_message'] = (isset($request->status_message)) ? $request->status_message : "";
      $logArr['response'] = (isset($request->data)) ? $request->data : $request->error;
      epsilon_harmony_log($logArr);

      if ($request->code == 200) {
        drupal_set_message(t('Record successfully created. Please check the epsilon logs for further details.'), 'status');
        return json_decode($request->data);
      }
      else {
        $error = (isset($request->data)) ? json_decode($request->data) : $request->error;
        if (isset($request->data)) {
          $error = $error->resultCode . " / " . $error->resultSubCode;
        }
        throw new Exception('Create record failed. Reason: ' . $error . '. Please check the epsilon logs for further details.');
      }
    }
    catch (Exception $e) {
      watchdog_exception("epsilon_harmony", $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      drupal_set_message($e->getMessage(), 'error');
    }
  }

  /**
   * Updates the record on Epsilon DB by calling the API.
   *
   * @param array $record
   *   Data to be passed through API.
   *
   * @return array
   *   Returns the response recieved from the API.
   */
  public function updateRecord($record) {
    try {
      $url = "https://api.harmony.eu.epsilon.com/v4/profiles/records/" . $record['CustomerKey'];
      $options = array(
        'method' => 'PUT',
        'headers' => array(
          'Authorization' => 'Bearer ' . self::getToken($this),
          'X-OUID' => $this->getXouid(),
          'Content-Type' => 'application/json',
        ),
        'data' => json_encode($record),
      );

      // HTTP Form request.
      $request = drupal_http_request($url, $options);

      // Log the API.
      $logArr['endpoint'] = $url;
      $logArr['status_code'] = (isset($request->code)) ? $request->code : "";
      $logArr['status_message'] = (isset($request->status_message)) ? $request->status_message : "";
      $logArr['header'] = json_encode($options['headers']);
      $logArr['request'] = json_encode($options['data']);
      $logArr['response'] = (isset($request->data)) ? $request->data : $request->error;
      epsilon_harmony_log($logArr);

      if ($request->code == 200) {
        drupal_set_message(t('Record successfully updated. Please check the epsilon logs for further details.'), 'status');
        return json_decode($request->data);
      }
      else {
        $error = (isset($request->data)) ? json_decode($request->data) : $request->error;
        if (isset($request->data)) {
          $error = $error->resultCode . " / " . $error->resultSubCode;
        }
        throw new Exception('Update record failed. Reason: ' . $error . '. Please check the epsilon logs for further details.');
      }
    }
    catch (Exception $e) {
      watchdog_exception("epsilon_harmony", $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      drupal_set_message($e->getMessage(), 'error');
    }
  }

  /**
   * Send a real time email via Epsilon.
   *
   * @param string $message_id
   *   Message ID key to be passed for a particular template to trigger.
   * @param array $record
   *   Data to be passed through API.
   *
   * @return array
   *   Returns the response recieved from the API.
   */
  public function sendMessage($message_id = NULL, $record = array()) {
    try {
      if ($message_id == NULL) {
        throw new Exception('Message ID not available.');
      }

      $url = "https://api.harmony.eu.epsilon.com/v3/messages/" . $this->getmessageId($message_id) . "/send";
      $options = array(
        'method' => 'PUT',
        'headers' => array(
          'Authorization' => 'Bearer ' . self::getToken($this),
          'X-OUID' => $this->getXouid(),
          'Content-Type' => 'application/json',
        ),
        'data' => json_encode($record),
      );

      // HTTP Form request.
      $request = drupal_http_request($url, $options);

      // Log the API.
      $logArr['endpoint'] = $url;
      $logArr['status_code'] = (isset($request->code)) ? $request->code : "";
      $logArr['status_message'] = (isset($request->status_message)) ? $request->status_message : "";
      $logArr['header'] = json_encode($options['headers']);
      $logArr['request'] = json_encode($options['data']);
      $logArr['response'] = (isset($request->data)) ? $request->data : $request->error;
      epsilon_harmony_log($logArr);

      if ($request->code == 200) {
        drupal_set_message(t('Message successfully sent. Please check the epsilon logs for further details.'), 'status');
        return json_decode($request->data);
      }
      else {
        $error = (isset($request->data)) ? json_decode($request->data) : $request->error;
        if (isset($request->data)) {
          $error = $error->resultCode;
        }
        throw new Exception('Message sending failed. Reason: ' . $error . '. Please check the epsilon logs for further details.');
      }
    }
    catch (Exception $e) {
      watchdog_exception("epsilon_harmony", $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      drupal_set_message($e->getMessage(), 'error');
    }
  }

  /**
   * Checks if the configurations are valid by making a token call.
   *
   * @return null
   *   Returns the response recieved from the API.
   */
  public function testApi() {
    try {
      $token = self::getToken($this, TRUE);
      drupal_set_message(t('All OK! Please check the logs for more details.'), 'status');
    }
    catch (Exception $e) {
      watchdog_exception("epsilon_harmony", $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      drupal_set_message($e->getMessage(), 'error');
    }
    drupal_goto('/admin/config/services/epsilon_harmony/configurations');
  }

}
