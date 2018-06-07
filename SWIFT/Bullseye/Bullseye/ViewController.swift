//
//  ViewController.swift
//  Bullseye
//
//  Created by Zharif Amin on 06/06/2018.
//  Copyright © 2018 Zharif Amin. All rights reserved.
//

import UIKit
import Foundation

class ViewController: UIViewController {
    
    var random = 0

    @IBOutlet weak var numLabel: UILabel!
    @IBOutlet weak var numSlider: UISlider!
    @IBOutlet weak var resultLabel: UILabel!
    @IBOutlet weak var exactSwitch: UISwitch!
    @IBOutlet weak var playAgainLabel: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        random = Int(arc4random_uniform(101))
        numLabel.text = "Move the slider to : \(random)"
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    @IBAction func sliderValueChange(_ sender: Any) {
        //numLabel.text = "\(round(numSlider.value))"
    }
    
    @IBAction func checkValue(_ sender: Any) {
        
        if exactSwitch.isOn == false {
            if Int(numSlider.value) >= random-3 &&
                Int(numSlider.value) <= random+3 {
                resultLabel.text = "You're correct. BULLSEYE"
                resultLabel.backgroundColor = UIColor.green
            }
            else{
                resultLabel.text = "You missed. Try again"
                resultLabel.backgroundColor = UIColor.red
            }
        }
        else {
            if random == Int(numSlider.value){
                resultLabel.text = "You're correct. BULLSEYE"
                resultLabel.backgroundColor = UIColor.green
            }
            else{
                resultLabel.text = "You missed. Try again"
                resultLabel.backgroundColor = UIColor.red
            }
        }
        resultLabel.isHidden = false
        playAgainLabel.isHidden = false
    }
    
    
    @IBAction func playAgainBtn(_ sender: Any) {
        numSlider.setValue(50, animated: false)
        random = Int(arc4random_uniform(101))
        numLabel.text = "Move the slider to : \(random)"
        resultLabel.isHidden = true
        playAgainLabel.isHidden = true
        
    }
}

