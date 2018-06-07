//
//  ViewController.swift
//  Tasbih Counter
//
//  Created by Zharif Amin on 06/06/2018.
//  Copyright © 2018 Zharif Amin. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    var counter = 0
    
    @IBOutlet weak var numLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    
    @IBAction func clickBtn(_ sender: UIButton) {
        counter += 1
        numLabel.text = "\(counter)"
    }


    @IBAction func resetBtn(_ sender: UIButton) {
        counter = 0
        numLabel.text = "\(counter)"
    }
}

