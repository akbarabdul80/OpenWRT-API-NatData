package dto

type ResponseUptime struct {
	Name       string `json:"name"`
	Last_entry int    `json:"last_entry"`
}
