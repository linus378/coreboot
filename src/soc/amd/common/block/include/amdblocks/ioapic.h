/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_BLOCK_IOAPIC_H
#define AMD_BLOCK_IOAPIC_H

/* Since the old APIC bus isn't used any more, the IOAPIC IDs can be < CONFIG_MAX_CPUS */
#define FCH_IOAPIC_ID		0
#define GNB_IOAPIC_ID		1

/* Index of IOAPIC resource associated with IOMMU */
#define IOMMU_IOAPIC_IDX                0x20000120

#endif /* AMD_BLOCK_IOAPIC_H */
