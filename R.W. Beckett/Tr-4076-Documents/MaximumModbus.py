from pymodbus.client.sync import ModbusSerialClient as ModbusClient
#This program uses the Python pymodbus package to read necessary registers
#to replicate a service report using the Serial adapter in replacement of the MyTechnician app.

#connect to the Genysis via serial adapter
port = ModbusClient(method='rtu',port='COM3',timeout=0.1,baudrate=116200)

#feild config
feildC = port.read_holding_registers(address = 2099,count = 20)
print(str(feildC.registers))

#lifetime history
lifeH = port.read_input_registers(address = 3399,count = 12)
print(str(lifeH.registers))

#50x Cycle History, read 10 at a time
for i in range(3999,4791,80):
    CycleHistory = port.read_input_registers(address = i,count = 80)
    print(str(CycleHistory.registers))

#50x Fault History, read 10 at a time
for i in range(5999,6791,80):
    FaultHistory = port.read_input_registers(address = i,count = 80)
    print(str(FaultHistory.registers))