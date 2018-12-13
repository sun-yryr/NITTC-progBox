import Foundation

func main() -> Int {
    let argv = ProcessInfo().arguments
    let argc = argv.count
    (0 ..< argc).forEach { print("argv[\($0)] = \(argv[$0])") }
    return 0
}
_ = main()