//add  surport 1 and other add 
//concat   surport 1 and orther add 
//same  Up    result +=str[i]


package main 
import (
    "fmt"
)

func add(a int, arg ...int) int {
    var sum int = a
    for i:=0; i<len(arg); i++ {
        sum += arg[i]
    }
    return  sum 
}
func main(){

    sum := add(2 ,3)
    fmt.Print(sum)

}



