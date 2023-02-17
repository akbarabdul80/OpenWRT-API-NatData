package dto

type ResponseTraffic struct {
	Name string  `json:"name"`
	Max  float32 `json:"max"`
}

type ResponseTrafficUD struct {
	Name     string  `json:"name"`
	Upload   float32 `json:"upload"`
	Download float32 `json:"download"`
}
