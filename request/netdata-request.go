package request_utlis

import (
	"encoding/json"

	"github.com/zerodev/oled_api_zerodev/dto"
	"github.com/zerodev/oled_api_zerodev/helper"
)

var serverUrl string

func init() {
	serverUrl = "http://127.0.0.1:19999/api/v1/"
}

func GetUptime() (dto.ResponseUptime, error) {
	httpRequest := helper.HTTPCurl{
		Method: "GET",
		Url:    serverUrl + "data?chart=system.uptime&_=1676449119812&format=json&points=485&group=average&gtime=0&options=ms|flip|jsonwrap|nonzero&after=-1",
	}

	response, err := httpRequest.Send()

	if err != nil {
		return dto.ResponseUptime{}, err
	}

	var uptimeObject dto.ResponseUptime
	json.Unmarshal([]byte(response), &uptimeObject)

	return uptimeObject, nil
}

func GetCPU() (dto.ResponseCPU, error) {
	httpRequest := helper.HTTPCurl{
		Method: "GET",
		Url:    serverUrl + "data?chart=system.cpu&_=1676443895083&format=array&points=1080&group=average&gtime=0&options=absolute%7Cjsonwrap%7Cnonzero&after=-1",
	}

	response, err := httpRequest.Send()

	if err != nil {
		return dto.ResponseCPU{}, err
	}

	var cpuObject dto.ResponseCPU
	json.Unmarshal([]byte(response), &cpuObject)

	return cpuObject, nil
}

func GetRAM() (dto.ResponseRAM, error) {
	httpRequest := helper.HTTPCurl{
		Method: "GET",
		Url:    serverUrl + "data?chart=system.ram&_=1676443931985&format=array&points=1080&group=average&gtime=0&options=absolute|percentage|jsonwrap|nonzero&after=-5&dimensions=used|buffers|active|wired",
	}

	response, err := httpRequest.Send()

	if err != nil {
		return dto.ResponseRAM{}, err
	}

	var ramObject dto.ResponseRAM
	json.Unmarshal([]byte(response), &ramObject)

	return ramObject, nil
}

func GetTraffic() (dto.ResponseTrafficUD, error) {
	httpRequestUP := helper.HTTPCurl{
		Method: "GET",
		Url:    serverUrl + "data?chart=system.net&_=1676630724767&format=array&points=1080&group=average&gtime=0&options=absolute|jsonwrap|nonzero&after=-1&dimensions=sent",
	}

	httpRequestDown := helper.HTTPCurl{
		Method: "GET",
		Url:    serverUrl + "data?chart=system.net&_=1676630724767&format=array&points=1080&group=average&gtime=0&options=absolute|jsonwrap|nonzero&after=-1&dimensions=received",
	}

	responseUp, errUP := httpRequestUP.Send()
	responseDown, errDown := httpRequestDown.Send()

	if errUP != nil && errDown != nil {
		return dto.ResponseTrafficUD{}, errDown
	}

	var upObject dto.ResponseTraffic
	var downObject dto.ResponseTraffic
	json.Unmarshal([]byte(responseUp), &upObject)
	json.Unmarshal([]byte(responseDown), &downObject)

	return dto.ResponseTrafficUD{Name: "Traffic", Upload: upObject.Max, Download: downObject.Max}, nil
}
