# EZ-PD&trade; PMG1 MCU: 12-bit SAR ADC basic

This code example demonstrates the method of using the 12-bit SAR ADC on EZ-PD&trade; PMG1-S3 MCU to read the input voltage applied in both differential and single-ended modes and to display the measured voltage and corresponding output codes in signed/unsigned format. It also explains the configuration of PASS 0 12-bit SAR ADC 0 using the Device Configurator on ModusToolbox&trade; software.

[View this README on GitHub.](https://github.com/Infineon/mtb-example-pmg1-12-bit-saradc-basic)

[Provide feedback on this code example.](https://cypress.co1.qualtrics.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMzQ2NDkiLCJTcGVjIE51bWJlciI6IjAwMi0zNDY0OSIsIkRvYyBUaXRsZSI6IkVaLVBEJnRyYWRlOyBQTUcxIE1DVTogMTItYml0IFNBUiBBREMgYmFzaWMiLCJyaWQiOiJlYXNvdmFyZ2hlc2UiLCJEb2MgdmVyc2lvbiI6IjEuMC4wIiwiRG9jIExhbmd1YWdlIjoiRW5nbGlzaCIsIkRvYyBEaXZpc2lvbiI6Ik1DRCIsIkRvYyBCVSI6IldJUkVEIiwiRG9jIEZhbWlseSI6IlRZUEUtQyJ9)


## Requirements

- [ModusToolbox&trade; software](https://www.cypress.com/products/modustoolbox-software-environment) v2.4 or later
- Set the `CY_SUPPORTED_KITS` environment variable with the value of "PMG1" to enable support for the PMG1 parts and BSPs in ModusToolbox&trade; software
- Board support package (BSP) minimum required version: 1.2.0
- Programming language: C
- Associated parts: [EZ-PD&trade; PMG1-S3 MCU](http://www.cypress.com/PMG1)


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm® Embedded Compiler v9.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.13 (`ARM`)
- IAR C/C++ Compiler v8.42.2 (`IAR`)

## Supported kits (make variable 'TARGET')

- [EZ-PD&trade; PMG1-S3 prototyping kit](http://www.cypress.com/CY7113) (`PMG1-CY7113`) – Default value of `TARGET`



## Hardware setup

1. Connect the board to your PC using a USB cable through the KitProg3 USB connector (J1). This cable is used for programming the PMG1 device and can be used during debugging. In addition, it transfers the UART data from the serial port to the PC to display it on a serial monitor.

2. Connect the USB PD port (J10) to a USB-C power adapter/USB port on PC using a Type-C/Type-A to Type-C cable to power the PMG1 device for normal operation.

3. By default, the ADC is configured to read differential input voltage applied across the Vplus and Vminus pins of PASS0 SARADC0. Make the following external wiring to apply a differential voltage to the ADC:

   1. Connect a 1k ohm/5k ohm potentiometer as input to apply analog voltage to the ADC.

   2. Wire up the end pins of the potentiometer to 3V3 pin (J6.1) and ground pin (J6.18).

   3. Connect the centre pin to P3.0 (J6.12) that is internally routed to the Vplus pin of PASS0 SARADC0.

   4. Connect P3.3 (J6.11) to ground pin (J6.3). This pin will be internally routed to the Vminus pin of PASS0 SARADC0 in differential input mode.

4. Do the following to use the ADC in single-ended input mode:

   1. Change the configuration in Device Configurator. See [Single-ended mode](#single-ended-mode).

   2. Remove the connection to the Vminus pin (J6.11).


See the kit user guide for details on configuring the board.


## Software setup

Install a terminal emulator to display the serial data. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).


## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox Application**). This launches the [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.cypress.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

This tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example will clone the "[Hello World](https://github.com/Infineon/mtb-example-pmg1-hello-world)" application with the desired name "MyHelloWorld" configured for the *PMG1-CY7110* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id PMG1-CY7110 --app-id mtb-example-pmg1-hello-world --user-app-name MyHelloWorld --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project Creator tools" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br>

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and then import the libraries using the `make getlibs` command.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation

1. Ensure that the steps listed in the [Hardware setup](#hardware-setup) section are completed.

2. Ensure that the jumper shunt on power selection jumper (J5) is placed at position 2-3 to enable programming mode.

3. Connect the board to your PC using the USB cable through the KitProg3 USB connector (J1). This cable is used for programming the PMG1 device.

4. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   	<details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain and target are specified in the application's Makefile but you can override those values manually:
      ```
      make program TARGET=<BSP> TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TARGET=PMG1-CY7113 TOOLCHAIN=GCC_ARM
      ```
     **Note:** This application supports only PMG1-CY7113 BSP.
   </details>

5. After programming the kit, disconnect the USB cable and change the position on the power selection jumper (J5) to 1-2 to power the kit through the USB PD port in operational mode.

6. Reconnect the USB cable to KitProg3 Type-C port (J1).

7. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

8. Power the kit through the USB PD port (J10), using the second USB cable.

   As soon as the kit is powered through the USB PD port, the application starts printing "Displaying 12-bit SAR ADC output: DIFFERENTIAL mode - Signed". Consequently, the digital output codes and the corresponding value of the measured analog input voltages are automatically displayed at an interval of 500 milliseconds each.

9. Measure the voltage applied to the Vplus/Vminus input of the ADC using a multimeter and compare with the corresponding voltages and digital codes displayed on the serial terminal, using the standard ADC conversion formula:

   Code = (Vin/Vref) * (2^n - 1), where 'n' is the resolution in number of bits used for representing the digital code.

10. Note that the ADC is configured in differential input mode by default. To change the input into single-ended/differential mode and also to choose the resultant output code format as signed/unsigned, see the configuration steps under the [Design and implementation](#design-and-implementation) section.

**Figure 1. UART terminal display of signed and unsigned code format**

<img src = "images/terminal-display.png" width = "1000"/>


## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**.

Ensure that the board is connected to your PC using the USB cables through both the KitProg3 USB connector and the USB PD port, with the jumper shunt on power selection jumper (J5) placed at position 1-2.

See the "Debug mode" section in the kit user guide for debugging the application on the CY7113 prototyping kit. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide).


## Design and implementation

This code example uses the 12-bit SAR ADC provided in the programmable analog block, available only on PMG1-S3 devices. This ADC can be configured using the Device Configurator tool in ModusToolbox&trade; software.

PASS0 SARADC0 has three inputs: Vplus, Vminus, and ext_vref. The inputs can be routed to the required external pins using a set of firmware-controlled switches used for analog routing.

PASS 0 12-bit SAR ADC 0 has two input modes: differential mode and single-ended mode. In differential input mode, a differential signal can be applied across the Vplus and Vminus input pins of the ADC. This mode is suitable for reading signals that vary in both positive and negative sides, such as an alternating current (AC) signal. Single-ended input modes are preferred for reading analog direct current (DC) signals. In addition to this, the output code can be displayed in both signed and unsigned formats.

Detailed configuration of PASS 0 12-bit SAR ADC 0 for parameters such as reference voltage, resolution, number of channels, scan rate, channel acquisition time, clock frequency, input mode, result format, interrupts and so on are included in the Device Configurator tool as shown below:

### PASS 0 12-bit SAR ADC 0 configuration

1. Select the application project in the Project Explorer.

2. In the **Quick Panel**, scroll down to **Tools** section, and click **Device Configurator 3.10**.

   **Figure 2. PASS 0 12-bit SAR ADC 0 configuration using Device Configurator 3.10**

   <img src = "images/saradc-configuration-1.png" width = "1000"/>

3. On the Device Configurator, select **PASS 0 12-bit SAR ADC 0** under **Programmable Analog (PASS) 0** in **Peripherals** tab. This opens the ADC configuration fields, and make the following changes:

   1. In the **Channel 0** section, select input modes as 'Differential' or 'Single-ended'.

   2. Under **Sampling** section, select the output result formats as 'Signed' or 'Unsigned'.

   3. Change other parameters to modify the performance of ADC per the application requirements.

   **Note:** If you make any changes on the Device Configurator save the changes and then re-program the kit to activate the new configuration.

   **Figure 3. PASS 0 12-bit SAR ADC 0 configuration using Device Configurator 3.10**

   <img src = "images/saradc-configuration-2.png" width = "1000"/>

   Some of the important parameters that are responsible for the performance of PASS 0 12-bit SAR ADC 0 are listed below:

   (a) To get the maximum resolution, choose **Internal BangGap Reference** as to 1.2 V, which is the lowest value of reference voltage (Vref).

   (b) Because of the low frequency operation of the ADC (between 1.7MHz and 1.8MHz), do not use the **bypass capacitor**.

   (c) Set the ADC **clock frequency** to 1.778 MHz using a suitable divider value to enable the operation without a Vref bypass capacitor.
       Note that any clock frequency greater than 1.8 MHz requires an external Vref bypass capacitor to be connected to the ext_vref pin for faithful code conversion.

   (d) Select **Full Resolution 12-bit** to ensure maximum performance of the ADC.

   (e) Set **Samples Averaged** to **256** to minimize the effect of noise and other errors. This results in averaging out 256 samples from a particular channel, in a single scan, to generate the final ADC output code value.

   (f) For a fixed clock frequency, **Achieved Free-Run Scan Rate (sps)** depends on **Target Scan Rate (sps)**, **Minimum Acquisition Time (ns)** and **Sampled Averaged**. See the 'Scan Rate' section in the [SAR ADC PDL API Reference](https://infineon.github.io/mtb-pdl-cat2/pdl_api_reference_manual/html/group__group__sar.html). Note that the achieved scan duration is 2.304 milliseconds for an acquisition time of 562 nanoseconds.

   **Note:** By default, the ADC is configured for **differential input**, with **signed output code format**. To modify the configuration between single-ended/differential input mode and signed/unsigned output code format, see [Differential mode](#differential-mode) and [Single-ended mode](#single-ended-mode).

   Note that the pins P3.0 and P3.3 are assigned to Vplus and Vminus inputs for PASS 0 12-bit SAR ADC 0 respectively. The internal signal routing can be viewed using the **Analog Routing** tab in the Device Configurator 3.10 as shown below.

   **Figure 4. Analog routing in Device Configurator 3.10**

   <img src = "images/analog-routing.png" width = "800"/>

**Note:** Port-2 pins are ideally reserved for connecting to PASS 0 12-bit SAR ADC 0 on PMG1-S3 devices. But in this example, port-2 pins cannot be used as they are wired onto other peripherals, in CY7113 prototyping kits. Therefore, in this example, connection to Vplus and Vminus are routed to other pins through AMUXBUSA/B as described in the **Info** tab in the **Notice List**.


#### Differential mode (default)

In differential input mode, a differential signal can be applied across the Vplus and Vminus pins of the PASS 0 12-bit SAR ADC 0. In this example, 1.2 V (internal bandgap reference) is set as the reference voltage (Vref) for the ADC.

In signed output code format (default), the differential code range in decimal value varies from -2048 (0x800) to 2047 (0x7FF), giving a total of 4095 digital codes:

   **Figure 5. Differential input- signed output code**

   <img src = "images/diff-signed.png" width = "600"/>

The code -2048 corresponds to the Vminus input equal to Vref (1.2 V) and Vplus input at ground (0 V). Similarly, code 2047 corresponds to the Vplus input equal to Vref (1.2 V) and Vminus input at ground (0 V). This can be achieved by interchanging the potentiometer input connection and the ground connection between the Vplus (J6.12) and Vminus (J6.11) pins of the ADC.

Differential result format can be changed to 'Unsigned' under **Sampling** section. In unsigned output code format, the differential code range in decimal value varies from 0 (0x000) to 4095 (0xFFF), giving a total of 4095 codes as follows:

   **Figure 6. Differential input - unsigned output code**

   <img src = "images/diff-unsigned.png" width = "600"/>

The code 0 corresponds to the Vminus input equal to Vref (1.2 V) and Vplus input at ground (0 V). Similarly, code 4095 corresponds to the Vplus input equal to Vref (1.2 V) and Vminus input at ground (0 V).


#### Single-ended mode

To change the ADC input mode from 'Differential' to 'Single-ended', navigate to the **Channel 0** tab in **PASS 0 12-bit SAR ADC 0** and change the **Input Mode** to **Single-ended**. Note that for single-ended mode, the connection to the Vminus input pin of the ADC must be removed as notified in the **Task** tab under the **Notice List**.

In single-ended input mode, an analog signal is applied to the Vplus input of the PASS 0 12-bit SAR ADC 0 with the Vneg pin connected internally to either of the three options: VSSA, Vref, or Routed.

In this example, Vneg is connected to **Vref** (1.2 V), under **Connections** in **PASS 0 12-bit SAR ADC 0**. Note that other values for reference signals such as VDDA or VDDA/2 or reference voltage from an external pin may also be used according to application requirements.

In signed output code format (default), the single-ended code range in decimal value varies from -2048 (0x800) to 2047 (0x7FF), giving a total of 4095 digital codes as shown in the figure below.

   **Figure 7. Single-ended input - signed output code**

   <img src = "images/se-signed.png" width = "600"/>

The code -2048 corresponds to the Vplus input at 0 V. Similarly, the code 2047 corresponds to the Vplus input equal to 2*Vref (2.4 V). Note that the potentiometer is powered from 3.3 V. Therefore, a full rotation of the potentiometer provides 3.3 V at the Vplus input of the ADC.

Single-ended result format can be changed to 'Unsigned' under **Sampling**. In the unsigned output code format, the single-ended code range in decimal value varies from 0 (0x000) to 4095 (0xFFF), giving a total of 4095 digital codes as follows:

   **Figure 8. Single-ended input - unsigned output code**

   <img src = "images/se-unsigned.png" width = "600"/>

The code 0 corresponds to the Vplus input at 0 V. Similarly, the code 4095 corresponds to the Vplus input equal to 2*Vref (2.4 V).

Note that the maximum voltage swing across Vplus and Vneg pin that the ADC can read is equal to Vref.

It implies that | Vplus - Vneg | <= Vref


   **Figure 9. Firmware flowchart**

   <img src = "images/firmware-flowchart.png" width = "300"/>

   **Note:** This ADC configuration results in a sample conversion delay of 2.304 milliseconds (scan duration) after triggering. This time interval may be effectively utilized to run codes to perform some user-defined tasks. However, a delay of 500 milliseconds has been allotted between each ADC sample display to slow down the UART terminal display rate for a better visibility.


### Resources and settings

**Table 1. Application resources**

| Resource  |  Alias/object     |    Purpose     |
| :------- | :------------    | :------------ |
| Programmable Analog (PASS) 0    	| PASS 0 12-bit SAR ADC 0       	| 12-bit SAR ADC is used to convert analog input voltage to digital codes|
| SCB 4			| CYBSP_UART			 	| UART SCB 4 block is used for serial communication, to send ADC code values through serial port|


## Related resources

Resources | Links
-----------|------------------
Application notes |[AN232553](https://www.cypress.com/an232553) – Getting started with EZ-PD&trade; PMG1 MCU on ModusToolbox&trade; software <br> [AN232565](https://www.cypress.com/an232565) – EZ-PD&trade; PMG1 MCU hardware design guidelines and checklist
Code examples | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [EZ-PD&trade; PMG1 MCU datasheets](https://www.cypress.com/PMG1DS)
Development kits | Select your kits from the [Evaluation Board Finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board) page.
Libraries on GitHub | [mtb-pdl-cat2](https://github.com/infineon/mtb-pdl-cat2) – Peripheral driver library (PDL) and docs <br> [mtb-hal-cat2](https://github.com/infineon/mtb-hal-cat2) – Hardware abstraction layer (HAL) library and docs
Tools | [Eclipse IDE for ModusToolbox&trade; software](https://www.cypress.com/modustoolbox) <br> ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon&reg; MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC™ Wi-Fi & Bluetooth® combo devices.


## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.

## Document history

Document title: *CE234649* – *EZ-PD&trade; PMG1 MCU: 12-bit SAR ADC basic*

| Version | Description of change |
| ------- | --------------------- |
| 1.0.0   | New code example      |
------

All other trademarks or registered trademarks referenced herein are the property of their respective owners.

-------------------------------------------------------------------------------

© Cypress Semiconductor Corporation, 2022. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates (“Cypress”).  This document, including any software or firmware included or referenced in this document (“Software”), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. No computing device can be absolutely secure. Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, “Security Breach”). Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach. In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes. It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product. “High-Risk Device” means any device or system whose failure could cause personal injury, death, or property damage. Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices. “Critical Component” means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness. Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
