package main 
import(
    "fmt"
    "strconv"
)

func main() {
    var str string
    fmt.Scanf("%s",&str)

    number,err := strconv.Atoi(str) 
    if err != nil{
        fmt.Print("fild")
        return 
    }

    fmt.Print(number)
}
