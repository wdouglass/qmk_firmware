定时器：
state.last_reset_update // 重启nrf模块计数器，每次重启一次开始计时，重启间隔为BiuNrf52ResetTimeout，默认30秒。模块开始工作后停止计时和重启
state.last_battery_update // 电池电压更新计时器，间隔BatteryUpdateInterval更新一次。
state.last_connection_update // 连接更新计时器，每次发送成功到nrf的包更新一次，（发送电池信息不更新
）
state.last_system_off_update // nrf休眠计时器，在非连接状态时进行计数，即用户进行配对且配对失败的情况下超时休眠

state.keep_connection_update // 用来保持连接的计时器，定时更新nrf的状态

休眠逻辑：
1：如果是连接状态，判断last_connection_update是否超时（超时间隔BiuNrf52SystemOffTimeout），即一段时间内没有按键
2：非连接状态，判断last_system_off_update是否超时（超时间隔BiuNrf52SystemOffTimeoutFast），即一段时间内没有连接，或者意外断开连接后一段时间

唤醒逻辑：

BLE SEND: 0XFF 0X4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0XFE 
    send_buf_send_one: have 0 remaining
    last connection update latency 1ms
  > BLE SEND: 0XFF 0X12 0XFE // * ask
  > Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
    recv latency 3ms, resp_buf size 1
  > Set the LED state as 2.
  > Set the LED state as 2.
  > Start Init the Nrf!!!
  > BLE SEND: 0XFF 0X12 0XFE 
    Put a time into resp buf, resp_buf size 1
    waited 1ms for resp_buf
    send_buf_send_one: have 0 remaining
  > Some thing wrong, resp_buf size 1
  > Start Init the Nrf!!!
    BLE SEND: 0XFF 0X12 0XFE 
  > Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
  > recv latency 1501ms, resp_buf size 1
    Start Configure the Nrf!!!
  > BLE SEND: 0XFF 0X12 0XFE 
    Put a time into resp buf, resp_buf size 1
    waited 1ms for resp_buf
    send_buf_send_one: have 0 remaining
  > recv latency 2ms, resp_buf size 1
    Set the LED state as 2.
  > Set the LED state as 2.
  > Start Init the Nrf!!!
    BLE SEND: 0XFF 0X12 0XFE 
  > Put a time into resp buf, resp_buf size 1
    waited 1ms for resp_buf
    send_buf_send_one: have 0 remaining
  > recv latency 1502ms, resp_buf size 1
    Set the LED state as 2.
  > Start Init the Nrf!!!
    BLE SEND: 0XFF 0X12 0XFE 
  > Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
  > recv latency 1501ms, resp_buf size 1
    Start Configure the Nrf!!!
  > BLE SEND: 0XFF 0X12 0XFE 
    Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
    recv latency 1ms, resp_buf size 1
    Set the LED state as 0.
  > Set the LED state as 0.
  > Start Init the Nrf!!!
    BLE SEND: 0XFF 0X12 0XFE 
  > Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
  > recv latency 1500ms, resp_buf size 1
    Start Configure the Nrf!!!
  > BLE SEND: 0XFF 0X12 0XFE 
    Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
    recv latency 1ms, resp_buf size 1
  > BLE SEND: 0XFF 0X12 0XFE 
    Put a time into resp buf, resp_buf size 1
    send_buf_send_one: have 0 remaining
    recv latency 3ms, resp_buf size 1
  > send latency 3ms
    BLE SEND: 0XFF 0X11 0XA 0XFE 
    send_buf_send_one
*** HID console disconnected (AA96:AA05:0001)
