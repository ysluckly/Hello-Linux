package main 

import(
    "fmt"
)

func multi(){
    for i:= 1; i<= 9; i++{
        for j := 1; j<=i;j++{
            fmt.Printf("%d * %d = %2d\t",i,j,i*j)
        }
        fmt.Println()
    }
}

func wanshu(n int) bool {
    var sum int 
    for i:= 1; i< n; i++ {
        if n %i  == 0 {
            sum += i
        }
    }

    if(n == sum){
        return true
    }else {
        return false
    }

}

func IsHuiwen(str string) bool{
    for i:= 0; i<len(str); i++{
        if i == len(str)/2 {
            break
        }
        last := len(str)-i-1
        if str[i] != str[last]{
            return false
        }

    }

    return true
}

func Count(str string) (a,b,c,d int) {
    return
}

func main(){

    var n int 
    fmt.Scanf("%d",&n)
    
    multi()
    if wanshu(n){
        fmt.Println("Is wanshu")
    }else{
        fmt.Println("Not")
    }
    
    var s string = "aaaaabbbbbbbaaaaa"
    if IsHuiwen(s){
        fmt.Println("Is Huiwen")
    }


}
