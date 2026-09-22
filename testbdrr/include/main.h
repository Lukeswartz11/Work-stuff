#ifndef MAIN_H
#define MAIN_H

    //Includes
    #include <stdint.h>
    #include "esp_twai.h"
    #include "esp_twai_onchip.h"

    //Rename type definitions
    typedef twai_node_handle_t Node;
    typedef twai_onchip_node_config_t nodeConfig;

    //declare global variables
    extern Node curNode;
    extern uint8_t SendBuffer[];
    extern uint8_t RecieveBuffer[];

    typedef enum{
        STATE_INIT,
        STATE_LISTEN,
        STATE_SEND
    } State;
    extern State curState;


    //function declorations
    void setupNode();
    void SendFrameFromBuffer(uint8_t *buffer);
    void Statemachine(State curstate);
    static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx);

#endif