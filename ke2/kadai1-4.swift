import Foundation

func main() -> Int {
    let argv = ProcessInfo().arguments
    if argv.count != 3 {
        print("引数が間違っています。")
        return -1
    }
    let inFoldername = argv[1]
    let outFoldername = argv[2]
    var inData :Dictionary<String, [Double]>
    
    for i in 1 ... 46 {
        var 
    }

    (0 ..< argv.count).forEach { print("argv[\($0)] = \(argv[$0])") }
    return 0
}

_ = main()