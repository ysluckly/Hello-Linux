package main 
import (
    "fmt"
)


func main(){
    var n int  
    fmt.Scanf("%d",&n)

    for i := 1; i<=n; i++ {
        for j:= 0; j< i; j++ {
            fmt.Print("A")
        }
        fmt.Println()

    }
}
