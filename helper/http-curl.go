package helper

import (
	"io/ioutil"
	"net/http"
)

// HTTPCurl is used for static shape json return
type HTTPCurl struct {
	Method  string
	Url     string
	Headers map[string]string
	Body    string
}

func (h *HTTPCurl) Send() (string, error) {
	client := &http.Client{}
	req, err := http.NewRequest(h.Method, h.Url, nil)
	if err != nil {
		return "", err
	}

	for key, value := range h.Headers {
		req.Header.Add(key, value)
	}

	resp, err := client.Do(req)
	if err != nil {
		return "", err
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}

	return string(body), nil
}
