-------------------------------------------------------------------------------
-- Practica2_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity Practica2_stub is
  port (
    leds : inout std_logic_vector(0 to 7);
    RX_pin : in std_logic;
    TX_pin : out std_logic;
    Rst_pin : in std_logic;
    Clk_pin : in std_logic;
    switch : inout std_logic_vector(0 to 7);
    banner_0_col_serial_out_pin : out std_logic;
    banner_0_col_clk_pin : out std_logic;
    banner_0_row_serial_out_pin : out std_logic;
    banner_0_row_clk_pin : out std_logic;
    banner_0_reset_out_pin : out std_logic;
    banner_0_reset2_out_pin : out std_logic;
    keypad_0_S_pin : out std_logic_vector(3 downto 0);
    keypad_0_R_pin : in std_logic_vector(3 downto 0);
    leds_rgb_0_red_pin : out std_logic;
    leds_rgb_0_green_pin : out std_logic;
    leds_rgb_0_blue_pin : out std_logic;
    altavoz_0_sonido_pin : out std_logic
  );
end Practica2_stub;

architecture STRUCTURE of Practica2_stub is

  component Practica2 is
    port (
      leds : inout std_logic_vector(0 to 7);
      RX_pin : in std_logic;
      TX_pin : out std_logic;
      Rst_pin : in std_logic;
      Clk_pin : in std_logic;
      switch : inout std_logic_vector(0 to 7);
      banner_0_col_serial_out_pin : out std_logic;
      banner_0_col_clk_pin : out std_logic;
      banner_0_row_serial_out_pin : out std_logic;
      banner_0_row_clk_pin : out std_logic;
      banner_0_reset_out_pin : out std_logic;
      banner_0_reset2_out_pin : out std_logic;
      keypad_0_S_pin : out std_logic_vector(3 downto 0);
      keypad_0_R_pin : in std_logic_vector(3 downto 0);
      leds_rgb_0_red_pin : out std_logic;
      leds_rgb_0_green_pin : out std_logic;
      leds_rgb_0_blue_pin : out std_logic;
      altavoz_0_sonido_pin : out std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of Practica2 : component is "user_black_box";

begin

  Practica2_i : Practica2
    port map (
      leds => leds,
      RX_pin => RX_pin,
      TX_pin => TX_pin,
      Rst_pin => Rst_pin,
      Clk_pin => Clk_pin,
      switch => switch,
      banner_0_col_serial_out_pin => banner_0_col_serial_out_pin,
      banner_0_col_clk_pin => banner_0_col_clk_pin,
      banner_0_row_serial_out_pin => banner_0_row_serial_out_pin,
      banner_0_row_clk_pin => banner_0_row_clk_pin,
      banner_0_reset_out_pin => banner_0_reset_out_pin,
      banner_0_reset2_out_pin => banner_0_reset2_out_pin,
      keypad_0_S_pin => keypad_0_S_pin,
      keypad_0_R_pin => keypad_0_R_pin,
      leds_rgb_0_red_pin => leds_rgb_0_red_pin,
      leds_rgb_0_green_pin => leds_rgb_0_green_pin,
      leds_rgb_0_blue_pin => leds_rgb_0_blue_pin,
      altavoz_0_sonido_pin => altavoz_0_sonido_pin
    );

end architecture STRUCTURE;

