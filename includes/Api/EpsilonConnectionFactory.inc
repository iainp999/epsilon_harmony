<?php

namespace EpsilonHarmonyConnector;

use Exception as Exception;

/**
 * Description for Connector Factory of Harmony API.
 *
 * @author Darshan Choudhary
 */
class EpsilonHarmonyConnectorFactory {

  /**
   * Client ID.
   *
   * @var string
   */
  private $clientId = NULL;

  /**
   * Secret Key.
   *
   * @var string
   */
  private $secretKey = NULL;

  /**
   * Username.
   *
   * @var string
   */
  private $username = NULL;

  /**
   * Password.
   *
   * @var string
   */
  private $password = NULL;

  /**
   * X-OUID.
   *
   * @var string
   */
  private $xouid = NULL;

  /**
   * Message ID.
   *
   * @var object
   */
  private $messageIdObject = NULL;

  /**
   * Access Token.
   *
   * @var string
   */
  protected static $accessToken;

  /**
   * Token Timeout.
   *
   * @var string
   */
  private $tokenTimeout = NULL;

  /**
   * Constructor. Should not be really used. Check the static methods.
   */
  public function __construct() {
    $this->setClientId(variable_get('epsilon_harmony_client_id', ''));
    $this->setsecretKey(variable_get('epsilon_harmony_secret_key', ''));
    $this->setUsername(variable_get('epsilon_harmony_username', ''));
    $this->setPassword(variable_get('epsilon_harmony_password', ''));
    $this->setXouid(variable_get('epsilon_harmony_xouid', ''));
    $this->setTokenTimeout(variable_get('epsilon_harmony_token_timeout', ''));
    $this->setMessageArray(variable_get('epsilon_harmony_message_id_array', ''));

    // Setting the static variable.
    self::$accessToken = variable_get('epsilon_harmony_access_token', '');
  }

  /**
   * Set the authentication username.
   *
   * @param string $username
   *   Username.
   *
   * @throws Exception
   *   Username must be at least 1 character long.
   */
  protected function setUsername($username) {
    // Check if the Harmony username is present.
    if (empty($username) || strlen($username) < 1) {
      throw new Exception('Harmony Username is missing.');
    }
    else {
      $this->username = $username;
    }
  }

  /**
   * Gets the assigned username.
   *
   * @return mixed
   *   Returns user name.
   */
  protected function getUsername() {
    return $this->username;
  }

  /**
   * Set the authentication password.
   *
   * @param string $password
   *   Password.
   *
   * @throws Exception
   *   Password must be at least 1 character long.
   */
  protected function setPassword($password) {
    // Check if the Harmony password is present.
    if (empty($password) || strlen($password) < 1) {
      throw new Exception('Harmony Password is missing.');
    }
    else {
      $this->password = $password;
    }
  }

  /**
   * Gets the assigned password.
   *
   * @return mixed
   *   Returns password.
   */
  protected function getPassword() {
    return $this->password;
  }

  /**
   * Set the authentication Client ID.
   *
   * @param string $clientId
   *   Client ID.
   *
   * @throws Exception
   *   Client ID must be at least 1 character long.
   */
  protected function setClientId($clientId) {
    // Check if the Harmony client ID is present.
    if (empty($clientId) || strlen($clientId) < 1) {
      throw new Exception('Harmony Client ID is missing.');
    }
    else {
      $this->clientId = $clientId;
    }
  }

  /**
   * Gets the assigned Client ID.
   *
   * @return mixed
   *   Returns Client ID.
   */
  protected function getClientId() {
    return $this->clientId;
  }

  /**
   * Set the authentication Secret Key.
   *
   * @param string $secretKey
   *   Secret Key.
   *
   * @throws Exception
   *   Secret Key must be at least 1 character long.
   */
  protected function setsecretKey($secretKey) {
    // Check if the Harmony Secret key is present.
    if (empty($secretKey) || strlen($secretKey) < 1) {
      throw new Exception('Harmony Secret Key is missing.');
    }
    else {
      $this->secretKey = $secretKey;
    }
  }

  /**
   * Gets the assigned Secret Key.
   *
   * @return mixed
   *   Returns Secret Key.
   */
  protected function getsecretKey() {
    return $this->secretKey;
  }

  /**
   * Set the authentication X-OUID.
   *
   * @param string $xouid
   *   X-OUID.
   *
   * @throws Exception
   *   X-OUID must be at least 1 character long.
   */
  protected function setXouid($xouid) {
    // Check if the Harmony X-OUID is present.
    if (empty($xouid) || strlen($xouid) < 1) {
      throw new Exception('X-OUID Key is missing.');
    }
    else {
      $this->xouid = $xouid;
    }
  }

  /**
   * Gets the assigned X-OUID.
   *
   * @return mixed
   *   Returns X-OUID.
   */
  protected function getXouid() {
    return $this->xouid;
  }

  /**
   * Set the Access token timeout.
   *
   * @param string $token_timeout
   *   Token Timeout.
   */
  protected function setTokenTimeout($token_timeout) {
    $this->tokenTimeout = $token_timeout;
  }

  /**
   * Gets the assigned Token Timeout.
   *
   * @return mixed
   *   Returns Token Timeout.
   */
  protected function getTokenTimeout() {
    return $this->tokenTimeout;
  }

  /**
   * Set message ID.
   *
   * @param string $message_ids
   *   Set message ID.
   */
  protected function setMessageArray($message_ids) {
    $this->messageIdObject = json_decode($message_ids);
  }

  /**
   * Returns Message ID.
   *
   * @param string $key
   *   Key for which message ID is to be retrieved.
   *
   * @return string
   *   Returns Message ID.
   */
  protected function getmessageId($key) {
    $message_ids = $this->messageIdObject;
    if (!isset($message_ids->$key)) {
      throw new Exception('Please enter a correct message identifier.');
    }
    return $message_ids->$key;
  }

  /**
   * Concatenate the client id and secret key.
   *
   * @return mixed
   *   Returns encoded Base64 value.
   */
  protected function getBaseToken() {
    return base64_encode($this->clientId . ":" . $this->secretKey);
  }

  /**
   * Process the form data to create a string to pass to API.
   * This method is to process the form data when content-type is
   * set to "application/x-www-form-urlencoded".
   *
   * @return string
   *   Returns stringified value of the form data.
   */
  protected function serializeData($data) {
    $i = 0;
    $string = "";
    foreach ($data as $key => $value) {
      if ($i == 0) {
        $string .= $key . "=" . $value;
      }
      else {
        $string .= "&" . $key . "=" . $value;
      }
      $i++;
    }
    return $string;
  }

}
