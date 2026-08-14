#Write new Value to feild configuration via seriral adapter
from pymodbus.client.sync import ModbusSerialClient as ModbusClient

#connect to the Genysis via serial adapter
port = ModbusClient(method='rtu',port='COM3',timeout=0.1,baudrate=116200)

#Read in the feild config
feildC = port.read_holding_registers(address = 2099,count = 20)

#optional print to veiw registers as a list for debugging
#print(feildC.registers)

#change one value of Feild config (must be the unlocked value)
#must change every time test is run to update the feild config
#(using max TFI tries, rotating between 0, 1, and 2)
feildC.registers[1] = 2

#write new registers to the controller
port.write_registers(address = 2099, values = feildC.registers)
