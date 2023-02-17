package dto

type ResponseALL struct {
	Name     string  `json:"name"`
	CPU      float32 `json:"cpu"`
	RAM      float32 `json:"ram"`
	Upload   float32 `json:"traffic_upload"`
	Download float32 `json:"traffic_download"`
	Uptime   float32 `json:"uptime"`
}
