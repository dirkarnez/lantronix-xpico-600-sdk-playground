var PageNav_currentmqttpage = "MqttStatusPage";
var mqttNav = new Navigator();
mqttNav.init(
    {
        navTable: [
            {
                navRowId: "Nav1",
                navRowLabel: "MQTT",
                navRowSetName: "PageNav_zerobasedline",
                navRowElements: NavRowElements_config_line_to_mqtt_example_MQTT_Instance,
                navRowMaxNumberOfCell: 4
            },
            {
                navRowId: "Nav2",
                navRowSetName: "PageNav_currentmqttpage",
                navRowElements: [
                    {
                        navRowElementLabel: "Status",
                        navRowElementSetValue: "'MqttStatusPage'"
                    },
                    {
                        navRowElementLabel: "Configuration",
                        navRowElementSetValue: "'MqttConfigPage'"
                    }
                ]
            }
        ],
        navOnClick: function () {
            if (PageNav_currentmqttpage == "MqttStatusPage") {
                mqttStatusPage.control.groups["status.MQTT"].instance = PageNav_zerobasedline;
                return mqttStatusPage.request();
            }
            else if (PageNav_currentmqttpage == "MqttConfigPage") {
                mqttConfigPage.control.groups["config.MQTT"].instance = PageNav_zerobasedline;
                return mqttConfigPage.request();
            }
            return false;
        }
    }
);
mqttNav.registerLeftMenu(
    {
        priority: 0,
        label: "MQTT",
        anchorId: "mqtt_Index",
        listClass: "navTitle"
    }
);
var mqttStatusPage = new SimplePage();
mqttStatusPage.init(
    {
        groups: {
            "status.MQTT": {
                instance: "0"
            }
        },
        automation: {
            layout: "status"
        }
    }
);
var mqttConfigPage = new SimplePage();
mqttConfigPage.init(
    {
        groups: {
            "config.MQTT": {
                instance: "0"
            }
        },
        automation: {
            layout: "configuration",
            simpleConfig: "mqttConf"
        }
    }
);
var mqttConf = new SimpleConf();
mqttConf.init(
	{
	    configGroup: {
	        "MQTT": {
	            instance: "0"
	        }
	    },
	    onTestSetSucceeded: {
	        automation: {
	            applyDisplayRulesFromSimplePage: mqttConfigPage
	        }
	    }
	}
);
