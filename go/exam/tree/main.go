package main

import "golang.org/x/tour/tree"
import "fmt"

// Walk walks the tree t sending all values
// from the tree to the channel ch.

func Walk(t *tree.Tree, ch chan int) {
	
	if t == nil {
		return
	}
	Walk(t.Left, ch)
	ch <- t.Value
	Walk(t.Right, ch)
}

/*
func Walk(t *tree.Tree, ch chan int) {
	defer close(ch)

	// requred "forward declaration" for recurive calls
	var walk func(t *tree.Tree)

	walk = func(t *tree.Tree) {
		if t == nil {
			return
		}
		walk(t.Left)
		ch <- t.Value
		walk(t.Right)
	}

	walk(t)
}
*/

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
	
	ch1, ch2 := make(chan int), make(chan int)
	defer close(ch1)
	defer close(ch2)
	
	go Walk(t1, ch1)
	go Walk(t2, ch2)
	
	for {
		v1, cont1 := <-ch1
		v2, cont2 := <-ch2

		fmt.Println(v1, v2)

		if !(v1 == v2 && cont1 == cont2) {
			return false
		} else if !cont1 {
			return true
		}
	}
}


func main() {
	
	t1 := tree.New(1)
	t2 := tree.New(2)
	t3 := tree.New(1)
	println(Same(t1, t3))
	println(Same(t1, t2))
}

