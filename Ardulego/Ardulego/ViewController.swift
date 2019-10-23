//
//  ViewController.swift
//  Ardulego
//
//  Created by Damian Charczuk on 8/17/19.
//  Copyright © 2019 Damian Charczuk. All rights reserved.
//

import UIKit
import CoreBluetooth

let hm10CBUUID = CBUUID(string: "0xFFE0")
let hm10CharacteristicCBUUID = CBUUID(string: "0xFFE1")
var hm10Characteristic : CBCharacteristic?

class ViewController: UIViewController {
    @IBOutlet weak var forwardButton: UIButton!
    @IBOutlet weak var reverseButton: UIButton!
    @IBOutlet weak var leftTurnSignalButton: UIButton!
    @IBOutlet weak var rightTurnSignalButton: UIButton!
    @IBOutlet weak var LEDSwitchButton: UIButton!
    @IBOutlet weak var MotorsSwitchButton: UIButton!
    
    var centralManager: CBCentralManager!
    var hm10Peripheral: CBPeripheral!

    var value : Int!
    var valueData : Data!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }

    
    @IBAction func onForwardPressed(_ sender: UIButton) {
        value = 2
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    @IBAction func onReversePressed(_ sender: UIButton) {
        value = 3
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    @IBAction func onLeftSignalPressed(_ sender: UIButton) {
        value = 4
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    @IBAction func onRightSignalPressed(_ sender: UIButton) {
        value = 5
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    @IBAction func onLEDPressed(_ sender: UIButton) {
        value = 0
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    @IBAction func onMotorsPressed(_ sender: UIButton) {
        value = 1
//        writeToPeripheral()
        writeValue(data: String(value))
    }
    
//    func writeToPeripheral(){
//        valueData = Data(bytes: &value, count: MemoryLayout.size(ofValue: value))
//        hm10Peripheral.writeValue(valueData.base64EncodedData(), for: hm10Characteristic!, type: CBCharacteristicWriteType.withResponse)
//        print("Value: \(String(describing: value))")
//        writeValue(data: String(value))
//    }
    
    func writeValue(data: String){
        let data = (data as NSString).data(using: String.Encoding.utf8.rawValue)
        if let peripheralDevice = hm10Peripheral{
            if let deviceCharacteristics = hm10Characteristic{
                peripheralDevice.writeValue((data)!, for: deviceCharacteristics, type: CBCharacteristicWriteType.withoutResponse)
            }
        }
    }
}

extension ViewController: CBCentralManagerDelegate {
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
        case .unknown:
            print("central.state is .unknown")
        case .resetting:
            print("central.state is .resetting")
        case .unsupported:
            print("central.state is .unsupported")
        case .unauthorized:
            print("central.state is .unauthorized")
        case .poweredOff:
            print("central.state is .poweredOff")
        case .poweredOn:
            print("central.state is .poweredOn")
            centralManager.scanForPeripherals(withServices: [hm10CBUUID])
        @unknown default:
            fatalError()
        }
    }

    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        print(peripheral)
        hm10Peripheral = peripheral
        hm10Peripheral.delegate = self
        centralManager.stopScan()
        central.connect(hm10Peripheral)
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("Connected!")
        hm10Peripheral.discoverServices([hm10CBUUID])
    }
}

extension ViewController: CBPeripheralDelegate{
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else { return }
        
        for service in services {
            print(service)
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService,
                    error: Error?) {
        guard let characteristics = service.characteristics else { return }
        
        for characteristic in characteristics {
            print(characteristic)
            if characteristic.properties.contains(.read) {
                print("\(characteristic.uuid): properties contains .read")
                peripheral.readValue(for: characteristic)
            }
            if characteristic.properties.contains(.notify) {
                print("\(characteristic.uuid): properties contains .notify")
                peripheral.setNotifyValue(true, for: characteristic)
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic,
                    error: Error?) {
        switch characteristic.uuid {
        case hm10CharacteristicCBUUID:
            print(characteristic.value ?? "no value")
            hm10Characteristic = characteristic
        default:
            print("Unhandled Characteristic UUID: \(characteristic.uuid)")
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didWriteValueFor characteristic: CBCharacteristic, error: Error?) {
        print("Value written")
    }
}
