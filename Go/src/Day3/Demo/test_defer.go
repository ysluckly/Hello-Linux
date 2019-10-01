package main 

import (
    "fmt"
)


//resource free  (file  lock   SQL)
func main(){
    var i int = 0 
    defer fmt.Println(i)
    i++
    defer fmt.Println(i)

    i++ 
    fmt.Println(i)
}
