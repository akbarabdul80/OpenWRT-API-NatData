package main

import (
	"log"

	"github.com/gin-gonic/gin"
	"github.com/zerodev/oled_api_zerodev/dto"
	"github.com/zerodev/oled_api_zerodev/helper"
	request_utlis "github.com/zerodev/oled_api_zerodev/request"
)

func main() {
	r := gin.Default()
	r.GET("/api", func(context *gin.Context) {

		// get uptime
		var uptimeObject dto.ResponseUptime
		uptimeObject, errUptime := request_utlis.GetUptime()

		// get cpu
		var cpuObject dto.ResponseCPU
		cpuObject, errCPU := request_utlis.GetCPU()

		// get ram
		var ramObject dto.ResponseRAM
		ramObject, errRAM := request_utlis.GetRAM()

		// get traffic
		var trafficObject dto.ResponseTrafficUD
		trafficObject, errTraffic := request_utlis.GetTraffic()

		if errUptime != nil && errCPU != nil && errRAM != nil && errTraffic != nil {
			res := helper.BuildErrorResponse("Error response", errUptime.Error(), nil)
			context.JSON(400, res)
			return
		}

		log.Println(ramObject.Max)

		var allObject dto.ResponseALL
		allObject.Name = "Zerodev"
		allObject.CPU = cpuObject.Max
		allObject.RAM = ramObject.Max
		allObject.Upload = trafficObject.Upload
		allObject.Download = trafficObject.Download
		allObject.Uptime = uptimeObject.Max

		res := helper.BuildResponse(true, "Data response", allObject)
		context.JSON(200, res)

	})
	r.Run()
}
