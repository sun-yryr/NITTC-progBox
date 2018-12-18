//
//  main.swift
//  kadai1-4
//
//  Created by 皆川泰陽 on 2018/12/13.
//  Copyright © 2018年 皆川泰陽. All rights reserved.
//

import Foundation
import Accelerate

func main() -> Int {
    let moji = ["あ","い","う","え","お","か","き","く","け","こ","さ","し","す","せ","そ","た","ち","つ","て","と","な","に","ぬ","ね","の","は","ひ","ふ","へ","ほ","ま","み","む","め","も","や","ゆ","よ","ら","り","る","れ","ろ","わ","を","ん"]
    print("H30 kadai1-4 4J38")
    let argv = ProcessInfo().arguments
    if argv.count != 2 {
        print("引数が間違っています。")
        return -1
    }
    let inFoldername = argv[1]
    var inFilenameSmp :[String] = Array(repeating: "\(inFoldername)/data", count: 46)
    var inFilenameAve :[String] = Array(repeating: "\(inFoldername)/average", count: 46)
    var inFilenameEgn :[String] = Array(repeating: "\(inFoldername)/jacobi", count: 46)
    var inFilenameVct :[String] = Array(repeating: "\(inFoldername)/jacobi_vector", count: 46)
    //  データへのパスを作る
    for i in 0 ..< 46 {
        inFilenameSmp[i] += String(format: "/c%02d.txt", i+1)
        inFilenameAve[i] += String(format: "/mean%02d.txt", i+1)
        inFilenameEgn[i] += String(format: "/data%02d.txt", i+1)
        inFilenameVct[i] += String(format: "/data%02d.txt", i+1)
    }
    //  inFilenameの中身のパスでファイルにアクセスし、各要素の配列を受け取る
    let sample :[[[Double]]] = inFilenameSmp.map({
        let tmpSmp :[Double] = filereadToDouble($0)
        var tmp :[[Double]] = Array(repeating: Array(repeating: 0.0, count: 196), count: 20);
        for i in 0 ..< 20 {
            for j in 0 ..< 196 {
                tmp[i][j] = tmpSmp[196*(160+i)+j]
            }
        }
        return tmp
    })
    let allAve :[[Double]] = inFilenameAve.map({filereadToDouble($0)})
    let allEgn :[[Double]] = inFilenameEgn.map({filereadToDouble($0)})
    let allVct :[[[Double]]] = inFilenameVct.map({
        let tmpVct :[Double] = filereadToDouble($0)
        var tmp :[[Double]] = Array(repeating: Array(repeating: 0.0, count: 196), count: 196);
        for i in 0 ..< 196 {
            for j in 0 ..< 196 {
                tmp[i][j] = tmpVct[196*i+j]
            }
        }
        return tmp
    })
    
    for i in 0 ..< sample.count {
        var ans_count = 0;
        for j in 0 ..< sample[0].count {
            let ans = maharanobis_minIndex(Target: sample[i][j], Average: allAve, EigenValue: allEgn, EigenVector: allVct)
            if (i == ans) {
                ans_count += 1
            }
            else {
                print("誤認識： \(moji[i]) -> \(moji[ans])")
            }
        }
        print("\(moji[i]) = \((Double(ans_count)/20.0)*100)% (\(ans_count)/20)")
    }
    
    print("finish")
    //let numarray = filereadToDouble("\(inFoldername)/sigma01.txt")
    //print(numarray[0])
    //var inData :Dictionary<String, [Double]>
    return 0
}

//  引数に与えられたPathのファイルにアクセスし、split("\n")で得られるDouble[]を返す
func filereadToDouble(_ filepath :String) -> [Double] {
    //print("read[\(filepath)]...")
    let url = URL(fileURLWithPath: filepath)
    let filedata = try! Data(contentsOf: url)
    let str = String(data: filedata, encoding: .utf8)!
    let array = str.split(separator: "\n")
    let returndata :[Double] = array.map({Double($0)!})
    return returndata
}

//  第一引数に与えられた文字データから、マハラノビス距離を計算し、距離最小のインデックスを返す(ex. あ -> 0)
//  エラーなら-1を返す
func maharanobis_minIndex(Target sampleData :[Double], Average aveData :[[Double]], EigenValue egnData :[[Double]], EigenVector vctData :[[[Double]]]) -> Int {
    var index = -1
    var ans = 10000000.0
    var xSubm: [Double]
    let d = 100.0
    for i in 0 ..< aveData.count {
        var tmp_d = 0.0
        xSubm = matrix_sub(Target: sampleData, Target2: aveData[i])
        for j in 0 ..< 180 {
            var tmp_xmek = 0.0
            for m in 0 ..< 196 {
                tmp_xmek += xSubm[m] * vctData[i][m][j]
            }
            tmp_xmek = tmp_xmek * tmp_xmek
            tmp_d += tmp_xmek/(egnData[i][j] + d)
        }
        if (ans > tmp_d) {
            ans = tmp_d
            index = i
        }
    }
    return index
}

func matrix_sub(Target A: [Double], Target2 B: [Double]) -> [Double] {
    var tmp: [Double] = Array(repeating: 0, count: A.count)
    (0 ..< A.count).forEach { (i) in
        tmp[i] = A[i] - B[i]
    }
    return tmp
}

func matrix_naiseki(Target A: [Double], Target2 B: [Double]) -> Double {
    var tmp = 0.0
    (0 ..< A.count).forEach { (i) in
        tmp = A[i] * B[i]
    }
    return tmp/Double(A.count)
}

_ = main()
