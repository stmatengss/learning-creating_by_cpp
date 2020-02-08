package main

import (
	"fmt"
	"sync"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
/*
func Crawl(url string, depth int, fetcher Fetcher) {
	
	count := 1
	ch_url := make(chan string)
	ch_dep := make(chan int)
	
	ch_urls := make(chan []string)
	ch_dep_n := make(chan int)
	
	ch_url <- url
	ch_dep <- depth

	worker1 := func() {
		for {
			depth_n := <- ch_dep
			url_n := <- ch_url
			count --
			
			println(url_n)
			
			if depth_n <= 0 {
				continue
			}
			body, urls, err := fetcher.Fetch(url_n)
			if err != nil {
				fmt.Println(err)
				continue
			}
			fmt.Printf("found: %s %q\n", url, body)
			
			ch_urls <- urls
			ch_dep_n <- (depth_n - 1)
		}
	}
	
	worker2 := func() {
		for {
			urls := <-ch_urls
			depth_n := <-ch_dep_n
			
			for _, u := range urls {
				count ++
				ch_dep <- depth_n
				ch_url <- u
			}
			if count == 0 {
				break
			}
		}
	}
	
	go worker1()
	
	go worker2()
	
	return
}
*/
var wg sync.WaitGroup

func Crawl(url string, depth int, fetcher Fetcher) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	
	defer wg.Done()
	
	if depth <= 0 {
		return
	}
	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		wg.Add(1)
		go Crawl(u, depth-1, fetcher)
	}
	return
}

func main() {
	wg.Add(1)
	go Crawl("https://golang.org/", 4, fetcher)
	wg.Wait()
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}

