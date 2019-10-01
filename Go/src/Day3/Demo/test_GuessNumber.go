package main 

import(
    "fmt"
    "math/rand"
)

func main(){
    
    n:=rand.Intn(100)

    for{
        var input int 
        fmt.Scanf("%d",&input)

        flag := false 
    
        
        switch{
        case input == n:
            fmt.Print("right\n")
            flag = true
        case input > n:
            fmt.Print("little\n")
        case input <n:
            fmt.Print("big\n")
        }

        if flag {
            break
        }
    }
}
