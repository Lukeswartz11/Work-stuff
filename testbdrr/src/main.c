#include "main.h"
#include "esp_twai.h"
#include "esp_twai_onchip.h"

#include <stdint.h>

//declare global variables
Node curNode = NULL;


//Create Node for sending the data
void setupNode() {
  //setup send data 
  nodeConfig curNodeConfig = {
      .io_cfg.tx = 4,               // TWAI TX GPIO pin
      .io_cfg.rx = 5,               // TWAI RX GPIO pin
      .bit_timing.bitrate = 200000, // 200 kbps bitrate (must all be the same baudrate)
      .tx_queue_depth = 5,          // Transmit queue depth set to 5
  };

  // Create a new TWAI controller driver instance
  ESP_ERROR_CHECK(twai_new_node_onchip(&curNodeConfig, &curNode));
  // Start the TWAI controller
  ESP_ERROR_CHECK(twai_node_enable(curNode));



  //setup receive data 
  twai_event_callbacks_t user_cbs = {
    .on_rx_done = twai_rx_cb,
  };
  ESP_ERROR_CHECK(twai_node_register_event_callbacks(curNode, &user_cbs, NULL));

}

static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
    uint8_t RecieveBuffer[8];
    twai_frame_t rx_frame = {
        .buffer = RecieveBuffer,
        .buffer_len = sizeof(RecieveBuffer),
    };
    if (ESP_OK == twai_node_receive_from_isr(handle, &rx_frame)) {
        // receive ok, do something here
    }
    return false;
}


void SendFrameFromBuffer(uint8_t *buffer){

  twai_frame_t tx_msg = {
      .header.id = 0x1,             // Message ID
      .header.ide = true,           // Use 29-bit extended ID format
      .buffer = buffer,             // Pointer to data to transmit
      .buffer_len = sizeof(buffer), // Length of data to transmit
  };

  ESP_ERROR_CHECK(twai_node_transmit(curNode, &tx_msg, 0));  // Timeout = 0: returns immediately if queue is full
  ESP_ERROR_CHECK(twai_node_transmit_wait_all_done(curNode, -1));  // Wait for transmission to finish

}


void app_main(void)
{
  uint8_t SendBuffer[] = "Hello World!";
  State curState = STATE_INIT;
  while(1){
    Statemachine(curState);
  }
}

//futuer state machine for a chip waiting on a signal from another and then sends info back
void Statemachine(State curState){

  switch(curState){

    case(STATE_INIT):
      setupNode();
      if (curNode != NULL){
        curState = STATE_LISTEN;
      }
      break;

    case(STATE_LISTEN):
      //listen for a responce from another controller
      curState = STATE_SEND;
      break;

    case(STATE_SEND):
      SendFrameFromBuffer(SendBuffer);
      break;

    default:
      curState = STATE_INIT;
      break;
  }

}
