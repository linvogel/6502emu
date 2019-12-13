import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Scanner;


public class Assembler6502 {
	
	public static final String PATTERN_LABEL_DEFINITION = "^[a-zA-Z][\\w]*:";
	public static final String PATTERN_LABEL_REFERENCE = "^\\.[a-zA-Z][\\w]*";
	public static final String PATTERN_OPCODE = "^([a-zA-Z]{3,3}[0-9]?([\\s]|[\\s]*#.*$|$))";
	
	public static final String PATTERN_ADDR_ABSOLUTE = "^((\\$[[:xdigit:]]{4})|(\\.[a-zA-Z][\\w]*))([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ABSOLUTE_INDEXED_INDIRECT = "^(\\(\\$[[:xdigit:]]{4}),[xX]\\)([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ABSOLUTE_INDEXED_X = "^(\\$[[:xdigit:]]{4}),[xX]([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ABSOLUTE_INDEXED_Y = "^(\\$[[:xdigit:]]{4}),[yY]([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ABSOLUTE_INDIRECT = "^(\\(\\$[[:xdigit:]]{4}\\))([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_IMMEDIATE = "^(#\\$[[:xdigit:]]{2})([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE = "^(\\$[[:xdigit:]]{2})([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE_INDEXED_INDIRECT = "^(\\(\\$[[:xdigit:]]{2}),[xX]\\)([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE_INDEXED_X = "^(\\$[[:xdigit:]]{4}),[xX]([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE_INDEXED_Y = "^(\\$[[:xdigit:]]{4}),[yY]([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE_INDIRECT = "^(\\(\\$[[:xdigit:]]{4}\\))([\\s]|[\\s]*#.*$|$)";
	public static final String PATTERN_ADDR_ZEROPAGE_INDIRECT_INDEXED_Y = "^(\\(\\$[[:xdigit:]]{2}\\)),[yY]([\\s]|[\\s]*#.*$|$)";
	
	private static Scanner scanner;
	private static PrintWriter printer;
	private static byte[] buffer = new byte[64*1024];
	private static int addr = 0;
	
	private static File input;
	private static File output;
	
	private static HashMap<String, Integer> labels = new HashMap<String, Integer>();
	private static HashMap<String, Integer> refs = new HashMap<String, Integer>();
	
	public static void main(String[] args) {
		try {
			for (int i = 0; i < args.length; i++) {
				if (args[i].equals("-o")) output = new File(args[++i]);
				else input = new File(args[i]);
			}
			if (input == null) System.err.println("FATAL: No input files specified!");
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("FATAL: Unexpected end of command line!");
		} catch (NullPointerException e) {}
		
		try {
			scanner = new Scanner(input);
			printer = new PrintWriter(output);
			
			while (hasLabelDef() || hasOpcode()) {
				if (hasLabelDef()) parseLabelDef();
				else if (hasOpcode()) parseOpcode();
			}
			
			
		} catch (IOException e) {
			System.err.println("FATAL: could not open a file for reading or writing: " + e.getLocalizedMessage());
		}
		
	}
	
	public static void parseOpcode() {
		String command = scanner.next(PATTERN_OPCODE);
		switch (command.toLowerCase()) {
			case "adc": parse_adc(); break;
			case "and": parse_and(); break;
			case "asl": parse_asl(); break;
			case "bbr0": parse_bbr0(); break;
			case "bbr1": parse_bbr1(); break;
			case "bbr2": parse_bbr2(); break;
			case "bbr3": parse_bbr3(); break;
			case "bbr4": parse_bbr4(); break;
			case "bbr5": parse_bbr5(); break;
			case "bbr6": parse_bbr6(); break;
			case "bbr7": parse_bbr7(); break;
			case "bbs0": parse_bbs0(); break;
			case "bbs1": parse_bbs1(); break;
			case "bbs2": parse_bbs2(); break;
			case "bbs3": parse_bbs3(); break;
			case "bbs4": parse_bbs4(); break;
			case "bbs5": parse_bbs5(); break;
			case "bbs6": parse_bbs6(); break;
			case "bbs7": parse_bbs7(); break;
			case "bcc": parse_bcc(); break;
			case "bcs": parse_bcs(); break;
			case "beq": parse_beq(); break;
			case "bit": parse_bit(); break;
			case "bmi": parse_bmi(); break;
			case "bne": parse_bne(); break;
			case "bpl": parse_bpl(); break;
			case "bra": parse_bra(); break;
			case "brk": parse_brk(); break;
			case "bvc": parse_bvc(); break;
			case "bvs": parse_bvs(); break;
			case "clc": parse_clc(); break;
			case "cld": parse_cld(); break;
			case "cli": parse_cli(); break;
			case "clv": parse_clv(); break;
			case "cmp": parse_cmp(); break;
			case "cpx": parse_cpx(); break;
			case "cpy": parse_cpy(); break;
			case "dec": parse_dec(); break;
			case "dex": parse_dex(); break;
			case "dey": parse_dey(); break;
			case "eor": parse_eor(); break;
			case "inc": parse_inc(); break;
			case "inx": parse_inx(); break;
			case "iny": parse_iny(); break;
			case "jmp": parse_jmp(); break;
			case "jsr": parse_jsr(); break;
			case "lda": parse_lda(); break;
			case "ldx": parse_ldx(); break;
			case "ldy": parse_ldy(); break;
			case "lsr": parse_lsr(); break;
			case "nop": parse_nop(); break;
			case "ora": parse_ora(); break;
			case "pha": parse_pha(); break;
			case "php": parse_php(); break;
			case "phx": parse_phx(); break;
			case "phy": parse_phy(); break;
			case "pla": parse_pla(); break;
			case "plp": parse_plp(); break;
			case "plx": parse_plx(); break;
			case "ply": parse_ply(); break;
			case "rmb0": parse_rmb0(); break;
			case "rmb1": parse_rmb1(); break;
			case "rmb2": parse_rmb2(); break;
			case "rmb3": parse_rmb3(); break;
			case "rmb4": parse_rmb4(); break;
			case "rmb5": parse_rmb5(); break;
			case "rmb6": parse_rmb6(); break;
			case "rmb7": parse_rmb7(); break;
			case "rol": parse_rol(); break;
			case "ror": parse_ror(); break;
			case "rti": parse_rti(); break;
			case "rts": parse_rts(); break;
			case "sbc": parse_sbc(); break;
			case "sec": parse_sec(); break;
			case "sed": parse_sed(); break;
			case "sei": parse_sei(); break;
			case "smb0": parse_smb0(); break;
			case "smb1": parse_smb1(); break;
			case "smb2": parse_smb2(); break;
			case "smb3": parse_smb3(); break;
			case "smb4": parse_smb4(); break;
			case "smb5": parse_smb5(); break;
			case "smb6": parse_smb6(); break;
			case "smb7": parse_smb7(); break;
			case "sta": parse_sta(); break;
			case "stp": parse_stp(); break;
			case "stx": parse_stx(); break;
			case "sty": parse_sty(); break;
			case "stz": parse_stz(); break;
			case "tax": parse_tax(); break;
			case "tay": parse_tay(); break;
			case "tsb": parse_tsb(); break;
			case "trb": parse_trb(); break;
			case "tsx": parse_tsx(); break;
			case "txa": parse_txa(); break;
			case "txs": parse_txs(); break;
			case "tya": parse_tya(); break;
			case "wai": parse_wai(); break;
		}
	}
	
	private static void parse_and() {
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
		if (has()) parse((byte)0x);
	}
	
	private static void parse_adc() {
		if (hasZeropageIndexedIndirect()) parseZeropageIndexedIndirect((byte)0x61);
		else if (hasZeropage()) parseZeropage((byte)0x65);
		else if (hasImmediate()) parseImmediate((byte)0x69);
		else if (hasAbsolute()) parseAbsolute((byte)0x6d);
		else if (hasZeropageIndirectYIndexed()) parseZeropageIndirectYIndexed((byte)0x71);
		else if (hasZeropageIndirect()) parseZeropageIndirect((byte)0x72);
		else if (hasZeropageXIndexed()) parseZeropageXIndexed((byte)0x75);
		else if (hasAbsoluteXIndexed()) parseAbsoluteXIndexed((byte)0x7d);
		else if (hasAbsoluteYIndexed()) parseAbsoluteXIndexed((byte)0x79);
	}
	
	public static boolean hasOpcode() {
		return scanner.hasNext(PATTERN_OPCODE);
	}
	
	public static boolean hasLabelDef() {
		return scanner.hasNext(PATTERN_LABEL_DEFINITION);
	}

	public static void parseLabelDef() {
		String label = scanner.next(PATTERN_LABEL_DEFINITION).split(":")[0];
		labels.put(label, addr);
	}
	
	public static boolean hasAbsolute() {
		return scanner.hasNext(PATTERN_ADDR_ABSOLUTE);
	}
	
	public static void parseAbsolute(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ABSOLUTE).substring(1, 5);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasAbsoluteIndexedIndirect() {
		return scanner.hasNext(PATTERN_ADDR_ABSOLUTE_INDEXED_INDIRECT);
	}
	
	public static void parseAbsoluteIndexedIndirect(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ABSOLUTE_INDEXED_INDIRECT).substring(2, 6);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasAbsoluteXIndexed() {
		return scanner.hasNext(PATTERN_ADDR_ABSOLUTE_INDEXED_X);
	}
	
	public static void parseAbsoluteXIndexed(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ABSOLUTE_INDEXED_X).substring(1, 5);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasAbsoluteYIndexed() {
		return scanner.hasNext(PATTERN_ADDR_ABSOLUTE_INDEXED_Y);
	}
	
	public static void parseAbsoluteYIndexed(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ABSOLUTE_INDEXED_Y).substring(1, 5);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasAbsoluteIndirect() {
		return scanner.hasNext(PATTERN_ADDR_ABSOLUTE_INDIRECT);
	}
	
	public static void parseAbsoluteIndirect(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ABSOLUTE_INDIRECT).substring(2, 6);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasImmediate() {
		return scanner.hasNext(PATTERN_ADDR_IMMEDIATE);
	}
	
	public static void parseImmediate(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_IMMEDIATE).substring(2, 6);
		short tmp = Short.parseShort(str, 16);
		buffer[addr++] = (byte) (tmp & 0xFF);
		buffer[addr++] = (byte) ((tmp >> 8) & 0xFF);
	}
	
	public static boolean hasZeropage() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE);
	}
	
	public static void parseZeropage(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE).substring(1, 3);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
	public static boolean hasZeropageIndexedIndirect() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE_INDEXED_INDIRECT);
	}
	
	public static void parseZeropageIndexedIndirect(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE_INDEXED_INDIRECT).split(",")[0].substring(2, 4);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
	public static boolean hasZeropageXIndexed() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE_INDEXED_X);
	}
	
	public static void parseZeropageXIndexed(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE_INDEXED_X).split(",")[0].substring(1, 3);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
	public static boolean hasZeropageYIndexed() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE_INDEXED_Y);
	}
	
	public static void parseZeropageYIndexed(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE_INDEXED_Y).split(",")[0].substring(1, 3);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
	public static boolean hasZeropageIndirect() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE_INDIRECT);
	}
	
	public static void parseZeropageIndirect(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE_INDIRECT).split(")")[0].substring(1, 3);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
	public static boolean hasZeropageIndirectYIndexed() {
		return scanner.hasNext(PATTERN_ADDR_ZEROPAGE_INDIRECT_INDEXED_Y);
	}
	
	public static void parseZeropageIndirectYIndexed(byte opcode) {
		buffer[addr++] = opcode;
		String str = scanner.next(PATTERN_ADDR_ZEROPAGE_INDIRECT_INDEXED_Y).split(",")[0].substring(2, 4);
		buffer[addr++] = Byte.parseByte(str, 16);
	}
	
}